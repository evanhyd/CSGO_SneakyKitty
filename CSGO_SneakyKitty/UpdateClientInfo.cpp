#include "UpdateClientInfo.h"

#include "offsets.h"
#include "module.h"
#include "memory.h"
#include "game_info.h"

#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

void UpdateClientInfo::operator()(int update_period_ms)
{
    while (true)
    {
        //read client state
        memory::ReadMem(module::csgo_process_handle, module::engine_dll + offsets::dwClientState, game_info::client_state);

        //read net channel
        memory::ReadMem(module::csgo_process_handle, game_info::client_state + offsets::clientstate_net_channel, game_info::net_channel);

        //read connection state
        memory::ReadMem(module::csgo_process_handle, game_info::client_state + offsets::dwClientState_State, game_info::connection_state);


        //if has connected to the server
        if (game_info::connection_state == client::kFullyConnected)
        {
            //read server info
            memory::ReadMem(module::csgo_process_handle, module::engine_dll + offsets::dwGlobalVars, game_info::server_info);

            //determine the server tick rate
            game_info::tick_rate = static_cast<int>(round(1.0f / game_info::server_info.interval_per_tick_));

            //read local player index
            memory::ReadMem(module::csgo_process_handle, game_info::client_state + offsets::dwClientState_GetLocalPlayer, game_info::local_player_index);

            //read entity address list
            memory::ReadMem(module::csgo_process_handle, module::client_dll + offsets::dwEntityList, game_info::player_entity_address_list);
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}