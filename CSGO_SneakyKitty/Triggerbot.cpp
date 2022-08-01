#include "Triggerbot.h"


bool Triggerbot::OnExecute()
{
    int entity_id;
    memory::ReadMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_iCrosshairId, entity_id);

    //valid entity index, alive, enemy
    if (0 <= entity_id && entity_id < game::kMaxPlayerNum &&
        game::player_is_valid[entity_id] &&
        game::player_list[game::local_player_index].IsEnemy(game::player_list[entity_id]))
    {
        memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::dwForceAttack, 6);
    }

    return false;
}