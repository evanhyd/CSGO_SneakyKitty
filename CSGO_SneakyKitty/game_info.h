#pragma once
#include <Windows.h>
#include "client.h"

#include "GlobalVar.h"
#include "PlayerEntityAddress.h"

namespace game_info
{
    //client info
    extern DWORD client_state;
    extern DWORD net_channel;
    extern int connection_state;

    extern GlobalVar server_info;
    extern int tick_rate;

    extern int local_player_index;
    extern PlayerEntityAddress player_entity_address_list[client::kMaxPlayerNum];



    //player entity list


    //player bone matrix list


    //player weapon


    //player input
}
