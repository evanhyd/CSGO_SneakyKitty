#include "RadarESP.h"


bool RadarESP::OnExecute()
{
    for (int entity_id = 0; entity_id < game::kMaxPlayerNum; ++entity_id)
    {
        if (game::player_is_valid[entity_id] && game::player_list[game::local_player_index].IsEnemy(game::player_list[entity_id]))
        {
            memory::WriteMem(module::csgo_proc_handle, game::player_address_list[entity_id].GetAddress() + offsets::m_bSpotted, true);
        }
    }

    return false;
}