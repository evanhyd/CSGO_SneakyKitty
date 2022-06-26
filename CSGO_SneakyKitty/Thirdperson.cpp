#include "Thirdperson.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "user_interface.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace user_interface;

void Thirdperson::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kThirdperson] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
            continue;
        }

        if(game::player_list[game::local_player_index].IsDead()) continue;

        int observe_mode;
        memory::ReadMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_iObserverMode, observe_mode);
        if (observe_mode == 0) observe_mode = 1;
        else observe_mode = 0;

        memory::WriteMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_iObserverMode, observe_mode);
        toggle_mode[kThirdperson] = 0;

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}
