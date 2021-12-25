#include "Bhop.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"

#include <iostream>
#include <thread>
#include <chrono>

void Bhop::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected || game::toggle_mode[game::bhop_hotkey] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        
        if (game::player_entity_list[game::local_player_index] .IsOnGround()  && GetAsyncKeyState('V'))
        {
            memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::dwForceJump, 6);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}