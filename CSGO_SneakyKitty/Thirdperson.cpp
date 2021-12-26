#include "Thirdperson.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"

#include <iostream>
#include <thread>
#include <chrono>

void Thirdperson::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected || game::toggle_mode[game::thirdperson_hotkey] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
            continue;
        }

        int observe_mode;
        memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[game::local_player_index].GetAddress() + offsets::m_iObserverMode, observe_mode);
        if (observe_mode == 0) observe_mode = 1;
        else observe_mode = 0;

        memory::WriteMem(module::csgo_proc_handle, game::player_entity_address_list[game::local_player_index].GetAddress() + offsets::m_iObserverMode, observe_mode);
        game::toggle_mode[game::thirdperson_hotkey] = 0;

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}