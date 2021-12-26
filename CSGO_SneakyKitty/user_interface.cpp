#include "user_interface.h"

#include "game.h"

#include <iostream>
#include <thread>
#include <chrono>

void user_interface::GUI()
{
    while (true)
    {
        if (GetAsyncKeyState(game::fakelag_hotkey))
        {
            if (game::toggle_mode[game::fakelag_hotkey] == 3) game::toggle_mode[game::fakelag_hotkey] = 0;
            else
            {
                game::toggle_mode[game::desync_hotkey] = 0;
                game::toggle_mode[game::aimbot_backtrack_hotkey] = 0;
                game::toggle_mode[game::fakelag_hotkey] += 1;
                std::cout << '\a';
            }
        }
        else if (GetAsyncKeyState(game::remove_flash_hotkey))
        {
            game::toggle_mode[game::remove_flash_hotkey] ^= 1;
            if (game::toggle_mode[game::remove_flash_hotkey] == 1) std::cout << '\a';
        }
        else if (GetAsyncKeyState(game::bhop_hotkey))
        {
            game::toggle_mode[game::bhop_hotkey] ^= 1;
            if (game::toggle_mode[game::bhop_hotkey] == 1) std::cout << '\a';
        }
        else if (GetAsyncKeyState(game::glow_esp_hotkey))
        {
            if (game::toggle_mode[game::glow_esp_hotkey] == 4) game::toggle_mode[game::glow_esp_hotkey] = 0;
            else
            {
                game::toggle_mode[game::glow_esp_hotkey] += 1;
                std::cout << '\a';
            }
        }
        else if (GetAsyncKeyState(game::radar_esp_hotkey))
        {
            game::toggle_mode[game::radar_esp_hotkey] ^= 1;
            if (game::toggle_mode[game::radar_esp_hotkey] == 1) std::cout << '\a';
        }
        else if (GetAsyncKeyState(game::thirdperson_hotkey))
        {
            game::toggle_mode[game::thirdperson_hotkey] = 1;
            std::cout << '\a';
        }
        else if (GetAsyncKeyState(game::desync_hotkey))
        {
            game::toggle_mode[game::fakelag_hotkey] = 0;
            game::toggle_mode[game::aimbot_backtrack_hotkey] = 0;
            game::toggle_mode[game::desync_hotkey] ^= 1;
            if (game::toggle_mode[game::desync_hotkey] == 1) std::cout << '\a';
        }
        else if (GetAsyncKeyState(game::aimbot_fire_hotkey))
        {
            if (game::toggle_mode[game::aimbot_fire_hotkey] == 3)
            {
                game::toggle_mode[game::aimbot_fire_hotkey] = 0;
                game::toggle_mode[game::aimbot_backtrack_hotkey] = 0;
            }
            else
            {
                game::toggle_mode[game::aimbot_fire_hotkey] += 1;
                std::cout << '\a';
            }
        }
        else if (GetAsyncKeyState(game::aimbot_backtrack_hotkey))
        {
            if (game::toggle_mode[game::aimbot_fire_hotkey] != 0)
            {
                game::toggle_mode[game::fakelag_hotkey] = 0;
                game::toggle_mode[game::desync_hotkey] = 0;
                game::toggle_mode[game::aimbot_backtrack_hotkey] ^= 1;
                if (game::toggle_mode[game::aimbot_backtrack_hotkey]) std::cout << '\a';
            }
        }
        else if (GetAsyncKeyState(game::global_target_hotkey))
        {
            game::toggle_mode[game::global_target_hotkey] ^= 1;
            if (game::toggle_mode[game::global_target_hotkey]) std::cout << '\a';
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}