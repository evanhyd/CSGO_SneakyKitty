#include "Bhop.h"


bool Bhop::OnExecute()
{
    int jump_state;
    memory::ReadMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_fFlags, jump_state);

    if (GetAsyncKeyState('V'))
    {
        if (jump_state & Entity::FL_ONGROUND) memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::dwForceJump, 6);
    }

    return false;
}