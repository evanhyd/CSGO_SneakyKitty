#include "Backtrack.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "Input.h"
#include "weapon.h"

#include <iostream>
#include <thread>
#include <chrono>


void Backtrack::operator()(int update_period_ms, int& curr_tick, int& backtrack_tick)
{
    Commands0X4 commands_0x4;

    while (true)
    {
        
        if (game::connection_state != client::kFullyConnected || game::toggle_mode[game::aimbot_backtrack_hotkey] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        if (GetAsyncKeyState('W') & 1 << 15 || GetAsyncKeyState('S') & 1 << 15 || GetAsyncKeyState('A') & 1 << 15 || GetAsyncKeyState('D') & 1 << 15)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            continue;
        }

        bool is_crouching = ((GetAsyncKeyState(VK_CONTROL) & 1 << 15) ? true : false);


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
        memory::ReadMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, commands_0x4);

        //update the current tick
        curr_tick = commands_0x4.tick_count_;

        //apply backtrack tick
        int cpy_backtrack_tick = backtrack_tick;
        if (cpy_backtrack_tick)
        {
            //activate if this weapon shoots this tick
            if (commands_0x4.buttons_mask_ & Input::IN_ATTACK)
            {
                commands_0x4.tick_count_ = cpy_backtrack_tick;

                if (is_crouching) commands_0x4.buttons_mask_ |= Input::IN_DUCK;

                memory::WriteMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, commands_0x4);
                memory::WriteMem(module::csgo_proc_handle, game::curr_verified_cmd_address + 0x4, commands_0x4);
            }
        }

        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}