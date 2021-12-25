#include "UpdateClientInfo.h"

#include "offsets.h"
#include "module.h"
#include "memory.h"
#include "game.h"

#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

void UpdateClientInfo::operator()(int update_period_ms)
{
    while (true)
    {
        //read client state
        memory::ReadMem(module::csgo_proc_handle, module::engine_dll + offsets::dwClientState, game::client_state);

        //read net channel
        memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::clientstate_net_channel, game::net_channel);

        //read connection state
        memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_State, game::connection_state);


        //if has connected to the server
        if (game::connection_state == client::kFullyConnected)
        {
            //read server info
            memory::ReadMem(module::csgo_proc_handle, module::engine_dll + offsets::dwGlobalVars, game::server_info);

            //determine the server tick rate
            game::tick_rate = static_cast<int>(round(1.0f / game::server_info.interval_per_tick_));

            //read local player index
            memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_GetLocalPlayer, game::local_player_index);

            //read entity address list
            memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwEntityList, game::player_entity_address_list);
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}