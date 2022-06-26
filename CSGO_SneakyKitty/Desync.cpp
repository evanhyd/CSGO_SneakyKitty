#include "Desync.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "Input.h"
#include "weapon.h"
#include "user_interface.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace user_interface;

void Desync::operator()(int update_period_ms)
{
    Angle client_view{};
    Commands0X4 cmd;

    constexpr float yaw_offset = 150.0f;
    float real_angle_y = yaw_offset;

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kDesync] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        //ground, grenade, planting C4
        if (!game::player_list[game::local_player_index].IsOnGround()) continue;
        if (weapon::IsGrenade(game::curr_weapon_def_index)) continue;
        if (weapon::IsC4(game::curr_weapon_def_index) && (GetAsyncKeyState(0x01) & 1 << 15)) continue;


        if (GetAsyncKeyState('A') & 1 << 15) real_angle_y = -yaw_offset;
        else if (GetAsyncKeyState('D') & 1 << 15) real_angle_y = yaw_offset;


        const bool is_crouching = (GetAsyncKeyState(VK_CONTROL) >> 15) & 1;

        
        //freeze the packet queue until it matches
        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, false);


        //wait until the cmd after the current cmd
        //there will be an unused tick between the outgoing and the incoming cmd (current cmd)
        const int incoming_cmd_num = game::last_outgoing_cmd_num + 2;

        //avoid perma disconnecting after game finishes
        while (game::connection_state == client::kFullyConnected)
        {
            int cmd_num;
            memory::ReadMem(module::csgo_proc_handle, game::net_channel + 0x18, cmd_num);
            if (cmd_num >= incoming_cmd_num) break;
        }

        //read the incoming user cmd
        memory::ReadMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, cmd);


        //read the engine angle
        memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, cmd.view_angles_);
        client_view = cmd.view_angles_;


        //force to even tick
        cmd.tick_count_ -= cmd.tick_count_ % 2;


        //stop shooting during the desync
        cmd.buttons_mask_ &= ~Input::IN_ATTACK;
        cmd.buttons_mask_ &= ~Input::IN_ATTACK2;


        //desync angle
        cmd.view_angles_.y_ += real_angle_y;
        cmd.view_angles_.Clamp();



        //fakewalk
        const float real_yaw = cmd.view_angles_.y_;

        //get moving status
        float forward_speed = 0.0f, sideway_speed = 0.0f;

        if (cmd.buttons_mask_ & Input::IN_FORWARD) forward_speed = 449.5f;
        else if (cmd.buttons_mask_ & Input::IN_BACK) forward_speed = -449.5f;

        if (cmd.buttons_mask_ & Input::IN_MOVERIGHT) sideway_speed = 449.5f;
        else if (cmd.buttons_mask_ & Input::IN_MOVELEFT) sideway_speed = -449.5f;



        //movement correction
        if (cmd.buttons_mask_ & (Input::IN_FORWARD | Input::IN_BACK | Input::IN_MOVERIGHT | Input::IN_MOVELEFT))
        {
            cmd.forward_move_ = forward_speed * cosf(Angle::ToRadians(real_yaw - client_view.y_)) +
                sideway_speed * sinf(-Angle::ToRadians(real_yaw - client_view.y_));

            cmd.side_move_ = forward_speed * sinf(Angle::ToRadians(real_yaw - client_view.y_)) +
                sideway_speed * cosf(-Angle::ToRadians(real_yaw - client_view.y_));

            //clamp the speed to avoid server side anti cheat
            cmd.forward_move_ = std::clamp(cmd.forward_move_, -449.5f, 449.5f);
            cmd.side_move_ = std::clamp(cmd.side_move_, -449.5f, 449.5f);
        }
        else
        {
            //micromovement
            if (cmd.tick_count_ % 4 == 2) cmd.side_move_ = (is_crouching ? 3.3f : 1.3f);
            else cmd.side_move_ = (is_crouching ? -3.3f : 1.3f);
        }

        


        memory::WriteMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, cmd);
        memory::WriteMem(module::csgo_proc_handle, game::curr_verified_cmd_address+ 0x4, cmd);
        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);
        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}