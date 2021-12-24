#pragma once
#include <Windows.h>
#include "client.h"

#include "GlobalVar.h"
#include "PlayerEntityAddress.h"
#include "PlayerEntity.h"

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
    extern PlayerEntity player_entity_list[client::kMaxPlayerNum];

    bool AreAlly(int player_entity_index_0, int player_entity_index_1);
    bool IsAVisibleToB(int entity_index_a, int entity_index_b);


    //player bone matrix list


    //player weapon


    //player input
}
