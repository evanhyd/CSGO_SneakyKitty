#include "RemoveFlash.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"


#include <iostream>
#include <thread>
#include <chrono>

void RemoveFlash::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected || game::toggle_mode[game::remove_flash_hotkey] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        //change max flash alpha persists for a long time (not tested)
        //memory::WriteMem(module::csgo_process_handle, game::player_entity_address_list[game::local_player_index].address_ + offsets::m_flFlashMaxAlpha, 80.0f);

        //change flash duration
        memory::WriteMem(module::csgo_proc_handle, game::player_entity_address_list[game::local_player_index].GetAddress() + offsets::m_flFlashDuration, 0.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}