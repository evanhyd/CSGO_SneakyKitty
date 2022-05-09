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

void Desync::operator()(int update_period_ms, float fake_walk_speed)
{
    Commands0X4 cmd;
    bool micromovement_direction = false;
    float real_angle_y = 119.0f;
    float real_angle_z = Angle::UPPER_ROLL;

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


        if (GetAsyncKeyState('W') & 1 << 15 || GetAsyncKeyState('S') & 1 << 15)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
            continue;
        }
        else if (GetAsyncKeyState('A') & 1 << 15)
        {
            real_angle_y = -119.0f;
            real_angle_z = Angle::UPPER_ROLL;
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
            continue;
        }
        else if (GetAsyncKeyState('D') & 1 << 15)
        {
            real_angle_y = 119.0f;
            real_angle_z = Angle::LOWER_ROLL;
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
            continue;
        }


        bool is_crouching = ((GetAsyncKeyState(VK_CONTROL) & 1 << 15) ? true : false);

        float fakewalk_magnitude = 0.0f;
        if (GetAsyncKeyState('X') & 1 << 15) fakewalk_magnitude = -fake_walk_speed;
        else if (GetAsyncKeyState('C') & 1 << 15) fakewalk_magnitude = fake_walk_speed;

        
        //freeze the packet queue until it matches
        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, false);


        //wait until the cmd after the current cmd
        //there will be an unused tick between the outgoing and the incoming cmd (current cmd)
        int incoming_cmd_num = game::last_outgoing_cmd_num + 2;

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


        //stop shooting during the desync
        cmd.buttons_mask_ &= ~Input::IN_ATTACK;
        cmd.buttons_mask_ &= ~Input::IN_ATTACK2;


        //micromovement and desync
        if (!is_crouching)
        {
            micromovement_direction = !micromovement_direction;
            cmd.side_move_ = (micromovement_direction ? 1.1f : -1.1f);

            cmd.view_angles_.y_ += -119.0f;
            cmd.view_angles_.z_ = Angle::UPPER_ROLL;

            real_angle_y = -119.0f;
        }
        else
        {
            micromovement_direction = !micromovement_direction;
            cmd.side_move_ = (micromovement_direction ? 3.3f : -3.3f);

            cmd.view_angles_.y_ += real_angle_y;
            cmd.view_angles_.z_ = real_angle_z;
        }

        cmd.view_angles_.Clamp();


        //fakewalk
        if (fakewalk_magnitude != 0.0f)
        {
            cmd.forward_move_ = fakewalk_magnitude * sinf(-Angle::ToRadians(real_angle_y));
            cmd.side_move_ = fakewalk_magnitude * cosf(-Angle::ToRadians(real_angle_y));
        }


        memory::WriteMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, cmd);
        memory::WriteMem(module::csgo_proc_handle, game::curr_verified_cmd_address+ 0x4, cmd);
        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}