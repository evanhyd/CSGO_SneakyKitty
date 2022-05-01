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

    
    //input info
    extern InputCmd input_cmd;
    extern int last_outgoing_cmd_num;
    extern DWORD curr_cmd_address;
    extern DWORD curr_verified_cmd_address;


    //hot key
    enum : uint8_t
    {
         fakelag_hotkey,
         remove_flash_hotkey,
         bhop_hotkey,
         glow_esp_hotkey,
         radar_esp_hotkey,
         thirdperson_hotkey,
         desync_hotkey,
         aimbot_fire_hotkey,
         aimbot_backtrack_hotkey,
         global_target_hotkey,
         bomb_timer_hotkey
    };
    

    extern short toggle_mode[255];
}
