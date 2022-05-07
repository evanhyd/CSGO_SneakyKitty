#include "Backtrack.h"

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

void Backtrack::operator()(int update_period_ms, int& current_tick, const int& backtrack_tick)
{
    Commands0X4 cmd;

    INPUT mouse_input{};
    mouse_input.type = INPUT_MOUSE;
    mouse_input.mi.dwFlags = MOUSEEVENTF_MOVE;
    mouse_input.mi.dwExtraInfo = 0;
    mouse_input.mi.time = 0;

    while (true)
    {
        
        if (game::connection_state != client::kFullyConnected || toggle_mode[kBacktrack] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        //moving + freezing packet causes teleport, sus as fk
        if (GetAsyncKeyState('W') & 1 << 15 || GetAsyncKeyState('S') & 1 << 15 || GetAsyncKeyState('A') & 1 << 15 || GetAsyncKeyState('D') & 1 << 15)
        {
            //simulate mouse left click
            if (GetAsyncKeyState(0x01) & (1 << 15)) SendInput(1, &mouse_input, sizeof(INPUT));
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            continue;
        }



        
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


        

        //update the current tick
        current_tick = cmd.tick_count_;

        
        //detect mouse left click
        if (GetAsyncKeyState(0x01) & (1 << 15))
        {
            int chosen_tick = backtrack_tick;
            if (chosen_tick > 0)
            {
                //apply backtrack
                cmd.buttons_mask_ |= Input::IN_ATTACK;
                if (GetAsyncKeyState(VK_CONTROL) & 1 << 15) cmd.buttons_mask_ |= Input::IN_DUCK;
                cmd.tick_count_ = chosen_tick;

                memory::WriteMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, cmd);
                memory::WriteMem(module::csgo_proc_handle, game::curr_verified_cmd_address + 0x4, cmd);
            }
            else
            {
                SendInput(1, &mouse_input, sizeof(INPUT));
            }
        }
        
        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}