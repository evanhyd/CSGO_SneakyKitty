#include "UpdateWeaponInfo.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "EntityAddress.h"
#include "weapon.h"

#include <iostream>
#include <thread>
#include <chrono>


void UpdateWeaponInfo::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        //read player's weapon entity index
        memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[game::local_player_index].GetAddress() + offsets::m_hActiveWeapon, game::curr_weapon_entity_index);

        //kepe the first 3 bytes
        game::curr_weapon_entity_index &= 0xfff;

		//note: this is entity, so we may be anble to render it
        memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwEntityList + (game::curr_weapon_entity_index - 1) * sizeof(EntityAddress), game::curr_weapon_entity_address);

        //normalize the weapon definition index range
        short temp_curr_weapon_def_index;
        memory::ReadMem(module::csgo_proc_handle, game::curr_weapon_entity_address + offsets::m_iItemDefinitionIndex, temp_curr_weapon_def_index);
        game::curr_weapon_def_index = (temp_curr_weapon_def_index < weapon::kMaxWeaponNum ? temp_curr_weapon_def_index : 0);

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}