#pragma once
#include <Windows.h>
#include "client.h"

#include "GlobalVar.h"
#include "EntityAddress.h"
#include "Entity.h"
#include "BoneMatrix.h"
#include "Input.h"

namespace game
{
    //client info
    extern DWORD client_state;
    extern DWORD net_channel;
    extern int connection_state;
    extern GlobalVar server_info;
    extern int tick_rate;
    extern int local_player_index;
    extern EntityAddress player_address_list[client::kMaxPlayerNum];


    //player entity list
    extern Entity player_list[client::kMaxPlayerNum];
    extern bool player_is_valid[client::kMaxPlayerNum];
    extern bool player_is_visible[client::kMaxPlayerNum]; //visible to local player, enemy only


    //player bone matrix list
    extern BoneMatrix bone_matrix_list[client::kMaxPlayerNum][BoneMatrix::kMaxBoneNum];


    //player weapon
    extern int curr_weapon_entity_index;
    extern DWORD curr_weapon_entity_address;
    extern short curr_weapon_def_index;

    
    //input info
    extern InputCmd input_cmd;
    extern int last_outgoing_cmd_num;
    extern DWORD curr_cmd_address;
    extern DWORD curr_verified_cmd_address;
}
