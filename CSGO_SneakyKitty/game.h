#pragma once
#include <Windows.h>
#include "client.h"

#include "GlobalVar.h"
#include "EntityAddress.h"
#include "Entity.h"
#include "BoneMatrix.h"

namespace game
{
    //client info
    extern DWORD client_state;
    extern DWORD net_channel;
    extern int connection_state;
    extern GlobalVar server_info;
    extern int tick_rate;
    extern int local_player_index;
    extern EntityAddress player_entity_address_list[client::kMaxPlayerNum];


    //player entity list
    extern Entity player_entity_list[client::kMaxPlayerNum];
    extern bool player_entity_is_valid[client::kMaxPlayerNum];
    extern bool player_entity_is_visible[client::kMaxPlayerNum]; //visible to local player, enemy only


    //player bone matrix list
    extern BoneMatrix bone_matrix_list[client::kMaxPlayerNum][BoneMatrix::kMaxBoneNum];


    //player weapon
    extern int curr_weapon_entity_index;
    extern DWORD curr_weapon_entity_address;
    extern short curr_weapon_def_index;


    //hot key
    extern byte fakelag_hotkey;
    extern byte remove_flash_hotkey;
    extern byte bhop_hotkey;
    extern byte glow_esp_hotkey;
    extern byte radar_esp_hotkey;
    extern byte thirdperson_hotkey;
    extern byte desync_hotkey;
    extern byte aimbot_fire_hotkey;
    extern byte aimbot_backtrack_hotkey;
    extern byte global_target_hotkey;
    extern byte rcs_hotkey;

    extern short toggle_mode[255];
}
