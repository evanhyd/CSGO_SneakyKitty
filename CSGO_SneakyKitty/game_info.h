#pragma once
#include <Windows.h>
#include "client.h"

namespace game_info
{
    extern int connection_state;

    extern DWORD client_state; //engine_dll + dwClientState
    extern DWORD net_channel; //client_state + clientstate_net_channel
    extern int local_player_index; //client_state + dwClientState_GetLocalPlayer

}
