#include "UpdateEntityInfo.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"

#include <iostream>
#include <thread>
#include <chrono>

void UpdateEntityInfo::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        //label all the player entities for future reference
        for (int i = 0; i < client::kMaxPlayerNum; ++i)
        {
            //address must not be null
            if (game::player_entity_address_list[i].GetAddress() == NULL)
            {
                game::player_entity_is_valid[i] = false;
                continue;
            }

            //read player entity info
            memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[i].GetAddress() + offsets::player_entity_struct_entry, game::player_entity_list[i]);


            //check team, dormant, health
            game::player_entity_is_valid[i] = 
                ((game::player_entity_list[i].GetTeam() == Entity::kT || game::player_entity_list[i].GetTeam() == Entity::kCT) &&
                !game::player_entity_list[i].IsDormant() && game::player_entity_list[i].GetHealth() > 0);
        }


        //update visibility
        for (int i = 0; i < client::kMaxPlayerNum; ++i)
        {
            game::player_entity_is_visible[i] = (game::player_entity_is_valid[i] && Entity::SpottedBy(i, game::local_player_index));
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}