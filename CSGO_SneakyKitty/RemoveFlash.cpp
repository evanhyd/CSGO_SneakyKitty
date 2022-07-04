#include "RemoveFlash.h"

bool RemoveFlash::OnExecute()
{
    //change flash duration
    memory::WriteMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_flFlashDuration, 0.0f);

    return false;
}