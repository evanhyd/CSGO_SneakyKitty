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
    /*INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_WHEEL;
    input.mi.time = NULL;
    input.mi.mouseData = 20;*/



    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kBhop] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        
        if (GetAsyncKeyState('V'))
        {
            memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::dwForceJump, 6);
            //SendInput(1, &input, sizeof(INPUT));
            
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}