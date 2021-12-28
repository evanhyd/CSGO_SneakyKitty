#include "user_interface.h"

#include "game.h"
#include "module.h"
#include "memory.h"
#include "offsets.h"

#include <cstdio>
#include <iostream>
#include <thread>
#include <chrono>

void user_interface::SendConsoleCommand(const std::string& command)
{
    COPYDATASTRUCT message;
    message.dwData = 0;
    message.lpData = (void*)(command.c_str());
    message.cbData = strlen(command.c_str()) + 1;
    SendMessageA(module::csgo_console_window, WM_COPYDATA, 0, reinterpret_cast<LPARAM>(&message));
}

void user_interface::SendBuiltInCommand(const std::string& command)
{
    if (command == "help")
    {
        std::cout << "Fakelag F6 (adaptive, C for lag, all time)\n";
        std::cout << "Remove Flash F7\n";
        std::cout << "Bhop F8\n";
        std::cout << "Glow ESP F9 (fullybody, inline, fullbody flickering, inline flickering)\n";
        std::cout << "Radar ESP F10\n";
        std::cout << "Thirdperson -\n";
        std::cout << "Desync Antiaim +\n";
        std::cout << "Aimbot [ (legit, rage1, rage2)\n";
        std::cout << "Backtrack (requires aimbot)\n";
        std::cout << "Global Target \\\n";

        std::cout << "\n\nBuilt-in commands:\n";
        std::cout << "/connect (fix the connection issue)\n";
        std::cout << "/record voice (K to record)\n";
        std::cout << "/update voice\n";
        std::cout << "/play voice (K to play)\n";
        std::cout << "/expose\n";
    }
    else if (command == "connect") memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);
    else if (command == "buy all pistols")
    {
        SendConsoleCommand("buy hkp2000");
        SendConsoleCommand("buy usp_silencer");
        SendConsoleCommand("buy elite");
        SendConsoleCommand("buy p250");
        SendConsoleCommand("buy tec9");
        SendConsoleCommand("buy fn57");
        SendConsoleCommand("buy deagle");
        SendConsoleCommand("buy glock");

        SendConsoleCommand("buy hkp2000");
        SendConsoleCommand("buy usp_silencer");
        SendConsoleCommand("buy elite");
        SendConsoleCommand("buy p250");
        SendConsoleCommand("buy tec9");
        SendConsoleCommand("buy fn57");
        SendConsoleCommand("buy deagle");
        SendConsoleCommand("buy glock");
    }
    else if (command == "drop all")
    {
        SendConsoleCommand("drop");
        SendConsoleCommand("drop");
    }
    else if (command == "update voice")
    {
        SendConsoleCommand("voice_inputfromfile 0");
        SendConsoleCommand("voice_recordtofile 0");

        std::remove("C:\\Users\\evanh\\works\\gaming\\steam\\steamapps\\common\\Counter-Strike Global Offensive\\voice_input.wav");
        int res = std::rename("C:\\Users\\evanh\\works\\gaming\\steam\\steamapps\\common\\Counter-Strike Global Offensive\\voice_decompressed.wav",
            "C:\\Users\\evanh\\works\\gaming\\steam\\steamapps\\common\\Counter-Strike Global Offensive\\voice_input.wav");
    }
    else if (command.find("record voice") != std::string::npos)
    {
        SendConsoleCommand("voice_inputfromfile 0");
        SendConsoleCommand("voice_recordtofile 1");
    }
    else if (command.find("play voice") != std::string::npos)
    {
        SendConsoleCommand("voice_recordtofile 0");
        SendConsoleCommand("voice_inputfromfile 1");
    }
    else if (command.find("expose") != std::string::npos)
    {

        for (int i = 0; i < client::kMaxPlayerNum; ++i)
        {
            if (!game::player_entity_is_valid[i]) continue;

            if (game::player_entity_list[game::local_player_index].IsEnemy(game::player_entity_list[i]))
            {
                char location[20] = "";
                memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[i].GetAddress() + offsets::m_szLastPlaceName, location);

                SendConsoleCommand("say_team Enemy Health: " + std::to_string(game::player_entity_list[i].GetHealth()) + " Location: " + location);
                Sleep(1000);
            }
        }
    }
}

void user_interface::AdjustConfig(const std::string& command)
{

}

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