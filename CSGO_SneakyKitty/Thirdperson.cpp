#include "Thirdperson.h"

bool Thirdperson::OnExecute()
{
    //check if local player is dead
    if (game::player_list[game::local_player_index].IsDead()) return false;

    int observe_mode;
    memory::ReadMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_iObserverMode, observe_mode);

    //switch angle
    if (observe_mode == 0) observe_mode = 1;
    else observe_mode = 0;

    memory::WriteMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_iObserverMode, observe_mode);
    user_interface::toggle_mode[user_interface::kThirdperson] = 0;

    return false;
}
