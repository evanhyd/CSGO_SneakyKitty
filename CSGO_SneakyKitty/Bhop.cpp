#include "Bhop.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "user_interface.h"

#include <iostream>
#include <thread>
#include <chrono>

#include "user_interface.h"

using namespace user_interface;

void Bhop::operator()(int update_period_ms)
{
    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kBhop] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        int jump_state;
        memory::ReadMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_fFlags, jump_state);

        if (GetAsyncKeyState('V'))
        {
            if(jump_state & Entity::FL_ONGROUND) memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::dwForceJump, 6);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}