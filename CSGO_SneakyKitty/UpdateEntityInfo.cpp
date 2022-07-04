#include "UpdateEntityInfo.h"


bool UpdateEntityInfo::OnExecute()
{
    //label all the player entities for future reference
    for (int entity_id = 0; entity_id < client::kMaxPlayerNum; ++entity_id)
    {
        //address must not be null
        if (game::player_address_list[entity_id].GetAddress() == NULL)
        {
            game::player_is_valid[entity_id] = false;
            continue;
        }

        //read player entity info
        memory::ReadMem(module::csgo_proc_handle, game::player_address_list[entity_id].GetAddress() + offsets::player_entity_struct_entry, game::player_list[entity_id]);


        //check team, dormant, health
        game::player_is_valid[entity_id] =
            ((game::player_list[entity_id].GetTeam() == Entity::kT || game::player_list[entity_id].GetTeam() == Entity::kCT) &&
             !game::player_list[entity_id].IsDormant() && game::player_list[entity_id].GetHealth() > 0);
    }


    //update visibility
    for (int entity_id = 0; entity_id < client::kMaxPlayerNum; ++entity_id)
    {
        game::player_is_visible[entity_id] = (game::player_is_valid[entity_id] && Entity::SpottedBy(entity_id, game::local_player_index));
    }

    return false;
}