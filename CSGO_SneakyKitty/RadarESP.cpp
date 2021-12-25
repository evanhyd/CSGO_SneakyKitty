#include "RadarESP.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"


#include <iostream>
#include <thread>
#include <chrono>

void RadarESP::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected || game::toggle_mode[game::radar_esp_hotkey] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        for (int i = 0; i < client::kMaxPlayerNum; ++i)
        {
            if (game::player_entity_is_valid[i] && !game::player_entity_list[game::local_player_index].IsAlly(game::player_entity_list[i]))
            {
                memory::WriteMem(module::csgo_proc_handle, game::player_entity_address_list[i].GetAddress() + offsets::m_bSpotted, true);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}