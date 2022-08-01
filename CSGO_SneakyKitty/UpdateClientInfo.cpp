#include "UpdateClientInfo.h"


bool UpdateClientInfo::OnExecute()
{
    //read client state
    memory::ReadMem(module::csgo_proc_handle, module::engine_dll + offsets::dwClientState, game::client_state);

    //read net channel
    memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::clientstate_net_channel, game::net_channel);

    //read connection state
    memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_State, game::connection_state);


    //if has connected to the server
    if (game::connection_state == game::kFullyConnected)
    {
        //read server info
        memory::ReadMem(module::csgo_proc_handle, module::engine_dll + offsets::dwGlobalVars, game::server_info);

        //determine the server tick rate
        game::tick_rate = static_cast<int>(round(1.0f / game::server_info.interval_per_tick_));

        //read local player index
        memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_GetLocalPlayer, game::local_player_index);

        //read entity address list
        memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwEntityList, game::player_address_list);
    }

    return false;
}