#include "user_interface.h"

#include "game.h"
#include "module.h"
#include "memory.h"
#include "offsets.h"

#include <cstdio>
#include <iostream>
#include <thread>
#include <chrono>

std::unordered_map <std::string, std::function<int(std::stringstream&)>> user_interface::command_map;

void user_interface::InitUserInterface()
{
    command_map.insert({ "help", CHelp });
    command_map.insert({ "connect", CConnect });
    command_map.insert({ "buy_all_pistols", CBuyAllPistols});
    command_map.insert({ "drop_all", CDropAll});
    command_map.insert({ "update_voice", CUpdateVoice});
    command_map.insert({ "record_voice", CRecordVoice});
    command_map.insert({ "play_voice", CPlayVoice});
    command_map.insert({ "sest_angle", CSetAngle});
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



void user_interface::SendConsoleCommand(const std::string& command_line)
{
    COPYDATASTRUCT message;
    message.dwData = 0;
    message.lpData = (void*)(command_line.c_str());
    message.cbData = strlen(command_line.c_str()) + 1;
    SendMessageA(module::csgo_console_window, WM_COPYDATA, 0, reinterpret_cast<LPARAM>(&message));
}

void user_interface::SendBuiltInCommand(const std::string& command_line)
{
    std::stringstream ss(command_line);
    std::string prefix;
    ss >> prefix;

    auto fn_iter = command_map.find(prefix);
    if (fn_iter != command_map.end()) fn_iter->second(ss);
    else std::cout << "Invalid Commands\a" << std::endl;
}


int user_interface::CHelp(std::stringstream& ss)
{
    std::cout << "Hot keys:\n";
    std::cout << "Fakelag F6 (adaptive, C for lag, all time)\n";
    std::cout << "Remove Flash F7\n";
    std::cout << "Bhop F8\n";
    std::cout << "Glow ESP F9 (fullybody, inline, fullbody flickering, inline flickering)\n";
    std::cout << "Radar ESP F10\n";
    std::cout << "Thirdperson -\n";
    std::cout << "Desync Antiaim +\n";
    std::cout << "Aimbot [ (legit, rage1, rage2)\n";
    std::cout << "Backtrack (requires aimbot)\n";
    std::cout << "Global Target \\ \n";


    std::cout << "\n\nBuilt-in commands:\n";
    std::cout << "/connect (fix the connection issue)\n";
    std::cout << "/record voice (K to record)\n";
    std::cout << "/update voice\n";
    std::cout << "/play voice (K to play)\n";
    std::cout << "/expose\n";
    std::cout << "/set angle [pitch/yaw/roll] [angle in degree]\n";

    std::cout << std::endl;

    return 0;
}

int user_interface::CConnect(std::stringstream& ss)
{
    memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);
    std::cout << "Reconnected" << std::endl;

    return 0;
}

int user_interface::CBuyAllPistols(std::stringstream& ss)
{
    SendConsoleCommand("buy elite");
    SendConsoleCommand("buy hkp2000");
    SendConsoleCommand("buy usp_silencer");
    SendConsoleCommand("buy glock");
    SendConsoleCommand("buy p250");
    SendConsoleCommand("buy tec9");
    SendConsoleCommand("buy fn57");
    SendConsoleCommand("buy deagle");


    SendConsoleCommand("buy elite");
    SendConsoleCommand("buy hkp2000");
    SendConsoleCommand("buy usp_silencer");
    SendConsoleCommand("buy glock");
    SendConsoleCommand("buy p250");
    SendConsoleCommand("buy tec9");
    SendConsoleCommand("buy fn57");
    SendConsoleCommand("buy deagle");

    return 0;
}

int user_interface::CDropAll(std::stringstream& ss)
{
    SendConsoleCommand("drop");
    SendConsoleCommand("drop");

    return 0;
}

int user_interface::CUpdateVoice(std::stringstream& ss)
{
    SendConsoleCommand("voice_inputfromfile 0");
    SendConsoleCommand("voice_recordtofile 0");

    std::remove("C:\\Users\\evanh\\works\\gaming\\steam\\steamapps\\common\\Counter-Strike Global Offensive\\voice_input.wav");
    int res = std::rename
    (
        "C:\\Users\\evanh\\works\\gaming\\steam\\steamapps\\common\\Counter-Strike Global Offensive\\voice_decompressed.wav",
        "C:\\Users\\evanh`\\works\\gaming\\steam\\steamapps\\common\\Counter-Strike Global Offensive\\voice_input.wav"
    );

    return 0;
}

int user_interface::CRecordVoice(std::stringstream& ss)
{
    SendConsoleCommand("voice_inputfromfile 0");
    SendConsoleCommand("voice_recordtofile 1");

    return 0;
}
int user_interface::CPlayVoice(std::stringstream& ss)
{
    SendConsoleCommand("voice_recordtofile 0");
    SendConsoleCommand("voice_inputfromfile 1");

    return 0;
}
int user_interface::CExpose(std::stringstream& ss)
{
    for (int i = 0; i < client::kMaxPlayerNum; ++i)
    {
        if (!game::player_entity_is_valid[i]) continue;

        if (game::player_entity_list[game::local_player_index].IsEnemy(game::player_entity_list[i]))
        {
            char location[20] = "";
            memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[i].GetAddress() + offsets::m_szLastPlaceName, location);

            SendConsoleCommand
            (
                "say_team Enemy Health: " + std::to_string(game::player_entity_list[i].GetHealth()) +
                " Location: " + location
            );
            Sleep(1000);
        }
    }

    return 0;
}


int user_interface::CSetAngle(std::stringstream& ss)
{
    Angle angle;
    ss >> angle.x_ >> angle.y_ >> angle.z_;
    angle.Clamp();

    memory::WriteMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, angle);
    return 0;
}