#include "Desync.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "Input.h"
#include "weapon.h"

#include <iostream>
#include <thread>
#include <chrono>

void Desync::operator()(int update_period_ms, float fake_walk_speed)
{
    Input input;
    Commands0X4 commands_0x4;
    bool micromovement_direction = false;
    float real_angle = 119.0f;

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || game::toggle_mode[game::desync_hotkey] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        //ground, grenade, planting C4
        if (!game::player_entity_list[game::local_player_index].IsOnGround()) continue;
        if (weapon::IsGrenade(game::curr_weapon_definition_index)) continue;
        if (weapon::IsC4(game::curr_weapon_definition_index) && (GetAsyncKeyState(0x01) & 1 << 15)) continue;


        if (GetAsyncKeyState('W') & 1 << 15 || GetAsyncKeyState('S') & 1 << 15)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
            continue;
        }
        else if (GetAsyncKeyState('A') & 1 << 15)
        {
            real_angle = -119.0f;
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
            continue;
        }
        else if (GetAsyncKeyState('D') & 1 << 15)
        {
            real_angle = 119.0f;
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
            continue;
        }

        bool is_crouching = ((GetAsyncKeyState(VK_CONTROL) & 1 << 15) ? true : false);

        float fakewalk_magnitude = 0.0f;
        if (GetAsyncKeyState('X') & 1 << 15) fakewalk_magnitude = -fake_walk_speed;
        else if (GetAsyncKeyState('C') & 1 << 15) fakewalk_magnitude = fake_walk_speed;


        //get input struct
        memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwInput, input);


        //get the last cmd number
        int last_outgoing_cmd_num;
        memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::clientstate_last_outgoing_command, last_outgoing_cmd_num);


        //calculate the incoming cmd address
        DWORD curr_user_cmd_addr = input.pCommands + ((last_outgoing_cmd_num + 1) % 150) * sizeof(Commands);
        DWORD curr_verified_user_cmd_addr = input.pVerifiedCommands + ((last_outgoing_cmd_num + 1) % 150) * sizeof(VerifiedCommands);

        
        //freeze the packet queue until it matches
        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, false);


        //wait until the current user cmd becomes the outgoing cmd
        //there will be an empty tick in between
        int curr_cmd_num = 0;
        int target_cmd_num = last_outgoing_cmd_num + 2;


        //avoid perma disconnecting after game finishes
        while (game::connection_state == client::kFullyConnected)
        {
            if (curr_cmd_num < target_cmd_num) memory::ReadMem(module::csgo_proc_handle, game::net_channel + 0x18, curr_cmd_num);
            else break;
        }


        //read the incoming user cmd address
        memory::ReadMem(module::csgo_proc_handle, curr_user_cmd_addr + 0x4, commands_0x4);


        //read the packet angle
        memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, commands_0x4.view_angles_);


        //stop shooting during the desync
        commands_0x4.buttons_mask_ &= ~Input::IN_ATTACK;
        commands_0x4.buttons_mask_ &= ~Input::IN_ATTACK2;


        //micromovement and desync
        if (!is_crouching)
        {
            commands_0x4.side_move_ = (micromovement_direction = !micromovement_direction) ? 1.1f : -1.1f;
            commands_0x4.view_angles_.y_ -= 119.0f;
            real_angle = -119.0f;
        }
        else
        {
            commands_0x4.side_move_ = (micromovement_direction = !micromovement_direction) ? 3.0f : -3.0f;
            commands_0x4.view_angles_.y_ += real_angle;
        }
        commands_0x4.view_angles_.Clamp();


        //fakewalk
        if (fakewalk_magnitude != 0.0f)
        {
            commands_0x4.forward_move_ = fakewalk_magnitude * sinf(Angle::ToRadians(-real_angle));
            commands_0x4.side_move_ = fakewalk_magnitude * cosf(Angle::ToRadians(-real_angle));
        }


        memory::WriteMem(module::csgo_proc_handle, curr_user_cmd_addr + 0x4, commands_0x4);
        memory::WriteMem(module::csgo_proc_handle, curr_verified_user_cmd_addr + 0x4, commands_0x4);


        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}