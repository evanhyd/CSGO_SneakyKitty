#include "BombTimer.h"
#include "memory.h"
#include "module.h"
#include "offsets.h"
#include "game.h"
#include "user_interface.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace user_interface;

void BombTimer::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kBombTimer] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        DWORD rule_proxy_address;
        bool is_bomb_planted;
        memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwGameRulesProxy, rule_proxy_address);
        memory::ReadMem(module::csgo_proc_handle, rule_proxy_address  + offsets::m_bBombPlanted, is_bomb_planted);

        //just planted the bomb
        if (is_bomb_planted)
        {
            const float no_kit_defused_time = game::server_info.curtime_ + 30.0f;
            const float kit_defused_time = game::server_info.curtime_ + 35.0f;

            while (game::server_info.curtime_ < no_kit_defused_time)
            {
                //check if defused
                memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwGameRulesProxy, rule_proxy_address);
                memory::ReadMem(module::csgo_proc_handle, rule_proxy_address + offsets::m_bBombPlanted, is_bomb_planted);
                if (!is_bomb_planted) break;

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }


            //requires kit to defuse
            if (is_bomb_planted)
            {
                std::cout << "\a" << std::endl;

                while (game::server_info.curtime_ < kit_defused_time)
                {
                    //check if defused
                    memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwGameRulesProxy, rule_proxy_address);
                    memory::ReadMem(module::csgo_proc_handle, rule_proxy_address + offsets::m_bBombPlanted, is_bomb_planted);
                    if (!is_bomb_planted) break;

                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }

                //too late to defuse
                std::cout << "\a" << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}