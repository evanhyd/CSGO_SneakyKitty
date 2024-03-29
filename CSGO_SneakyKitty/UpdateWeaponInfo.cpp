#include "UpdateWeaponInfo.h"

#include "EntityAddress.h"
#include "weapon.h"


bool UpdateWeaponInfo::OnExecute() 
{
    //read player's weapon entity index
    memory::ReadMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_hActiveWeapon, game::curr_weapon_entity_index);

    //kepe the first 3 uint8_ts
    game::curr_weapon_entity_index &= 0xfff;

    //note: this is entity, so we may be anble to render it
    memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::dwEntityList + (game::curr_weapon_entity_index - 1) * sizeof(EntityAddress), game::curr_weapon_entity_address);

    //normalize the weapon definition index range
    short temp_curr_weapon_def_index;
    memory::ReadMem(module::csgo_proc_handle, game::curr_weapon_entity_address + offsets::m_iItemDefinitionIndex, temp_curr_weapon_def_index);
    game::curr_weapon_def_index = (0 <= temp_curr_weapon_def_index && temp_curr_weapon_def_index < weapon::kMaxWeaponNum ? temp_curr_weapon_def_index : 0);

    return false;
}