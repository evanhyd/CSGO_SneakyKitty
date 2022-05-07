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
    constexpr int kScrollTime = 10;
    INPUT input[kScrollTime];
    
    for (int i = 0; i < kScrollTime; i++)
    {
        input[i].type = INPUT_MOUSE;
        input[i].mi.dwFlags = MOUSEEVENTF_WHEEL;
        input[i].mi.time = 0;
        input[i].mi.mouseData = -100;
        input[i].mi.dwExtraInfo = 0;
    }


    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kBhop] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        
        if (GetAsyncKeyState('V'))
        {
            //memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::dwForceJump, 6);
            SendInput(kScrollTime, input, sizeof(INPUT));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}