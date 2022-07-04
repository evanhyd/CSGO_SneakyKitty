#include "UpdateInputInfo.h"


#include "Input.h"
#include "weapon.h"

bool UpdateInputInfo::OnExecute()
{
    //read the input
    memory::ReadMem(module::csgo_proc_handle, module::client_dll + offsets::input_cmd_entry, game::input_cmd);

    //get the last cmd number
    memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::clientstate_last_outgoing_command, game::last_outgoing_cmd_num);

    //calculate the current cmd address
    game::curr_cmd_address = game::input_cmd.pCommands_ + ((game::last_outgoing_cmd_num + 1) % 150) * sizeof(Commands);
    game::curr_verified_cmd_address = game::input_cmd.pVerifiedCommands_ + ((game::last_outgoing_cmd_num + 1) % 150) * sizeof(VerifiedCommands);

    return false;
}