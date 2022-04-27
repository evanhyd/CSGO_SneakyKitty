#include "user_interface.h"

#include "game.h"
#include "module.h"
#include "memory.h"
#include "offsets.h"

#include <cstdio>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <ctime>

std::unordered_map <std::string, std::function<int(std::stringstream&)>> user_interface::command_map;

void user_interface::InitUserInterface()
{
    command_map.insert({ "fakelag", HFakeLag });
    command_map.insert({ "remove_flash", HRemoveFlash});
    command_map.insert({ "bhop", HBhop});
    command_map.insert({ "glow_esp", HGlowESP});
    command_map.insert({ "radar_esp", HRadarESP});
    command_map.insert({ "thirdperson", HThirdperson});
    command_map.insert({ "desync", HDesync});
    command_map.insert({ "aimbot", HAimbot});
    command_map.insert({ "backtrack", HBacktrack});
    command_map.insert({ "global_target", HGlobalTarget});


    command_map.insert({ "help", CHelp });
    command_map.insert({ "status", CStatus});
    command_map.insert({ "connect", CConnect });
    command_map.insert({ "buy_all_pistols", CBuyAllPistols});
    command_map.insert({ "drop_all", CDropAll});
    command_map.insert({ "update_voice", CUpdateVoice});
    command_map.insert({ "record_voice", CRecordVoice});
    command_map.insert({ "play_voice", CPlayVoice});
    command_map.insert({ "expose", CExpose});
    command_map.insert({ "set_angle", CSetAngle});
    command_map.insert({ "record_pos", CRecordPos });
    command_map.insert({ "config", CGameConfig });


    command_map.insert({ "test", CTest });
}



void user_interface::SendConsoleCommand(const std::string& command_line)
{
    COPYDATASTRUCT message;
    message.dwData = 0;
    message.lpData = (void*)(command_line.c_str());
    message.cbData = command_line.size() + 1;
    SendMessageA(module::csgo_console_window, WM_COPYDATA, 0, reinterpret_cast<LPARAM>(&message));
}
void user_interface::SendConsoleCommand(const std::u8string& command_line)
{
    COPYDATASTRUCT message;
    message.dwData = 0;
    message.lpData = (void*)(command_line.c_str());
    message.cbData = command_line.size() + 1;
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




int user_interface::HFakeLag(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(3));

    if (mode != 0)
    {
        game::toggle_mode[game::desync_hotkey] = 0;
        game::toggle_mode[game::aimbot_backtrack_hotkey] = 0;
        std::cout << '\a';
    }
    game::toggle_mode[game::fakelag_hotkey] = mode;

    return 0;
}
int user_interface::HRemoveFlash(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    game::toggle_mode[game::remove_flash_hotkey] = mode;

    return 0;
}
int user_interface::HBhop(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    game::toggle_mode[game::bhop_hotkey] = mode;

    return 0;
}
int user_interface::HGlowESP(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(4));

    if (mode != 0) std::cout << '\a';
    game::toggle_mode[game::glow_esp_hotkey] = mode;

    return 0;
}
int user_interface::HRadarESP(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    game::toggle_mode[game::radar_esp_hotkey] = mode;

    return 0;
}
int user_interface::HThirdperson(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    game::toggle_mode[game::thirdperson_hotkey] = mode;

    return 0;
}
int user_interface::HDesync(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0)
    {
        game::toggle_mode[game::fakelag_hotkey] = 0;
        game::toggle_mode[game::aimbot_backtrack_hotkey] = 0;
        std::cout << '\a';
    }
    game::toggle_mode[game::desync_hotkey] = mode;

    return 0;
}
int user_interface::HAimbot(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(3));

    if (mode != 0) std::cout << '\a';
    else game::toggle_mode[game::aimbot_backtrack_hotkey] = 0;

    game::toggle_mode[game::aimbot_fire_hotkey] = mode;

    return 0;
}
int user_interface::HBacktrack(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (game::toggle_mode[game::aimbot_fire_hotkey] != 0)
    {
        if (mode != 0)
        {
            game::toggle_mode[game::fakelag_hotkey] = 0;
            game::toggle_mode[game::desync_hotkey] = 0;
            std::cout << '\a';
        }
        game::toggle_mode[game::aimbot_backtrack_hotkey] = mode;
    }

    return 0;
}
int user_interface::HGlobalTarget(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    game::toggle_mode[game::global_target_hotkey] = mode;

    return 0;
}


int user_interface::CHelp([[maybe_unused]]std::stringstream& ss)
{
    std::cout << "Features:\n";
    std::cout << "/fakelag (adaptive, C for lag, all time)\n";
    std::cout << "/remove_flash\n";
    std::cout << "/bhop\n";
    std::cout << "/glow_esp (fullybody, inline, fullbody flickering, inline flickering)\n";
    std::cout << "/radar_esp\n";
    std::cout << "/thirdperson\n";
    std::cout << "/desync\n";
    std::cout << "/aimbot(legit, rage1, rage2)\n";
    std::cout << "/backtrack(requires aimbot)\n";
    std::cout << "/global target\n";


    std::cout << "\n\nBuilt-in commands:\n";
    std::cout << "/help\n";
    std::cout << "/status\n";
    std::cout << "/in_game_config\n";
    std::cout << "/connect (fix the connection issue)\n";

    std::cout << "/record voice (K to record)\n";
    std::cout << "/update voice\n";
    std::cout << "/play voice (K to play)\n";

    std::cout << "/record_pos\n";
    std::cout << "/expose\n";
    std::cout << "/set_angle [pitch/yaw/roll] [angle in degree]\n";
    std::cout << "/buy_all_pistols\n";
    std::cout << "/drop_all\n";

    std::cout << std::endl;

    return 0;
}

int user_interface::CStatus([[maybe_unused]] std::stringstream& ss)
{
    std::cout << "Toggle Status\n";

    if(game::toggle_mode[game::fakelag_hotkey]) std::cout << "fakelag: " << game::toggle_mode[game::fakelag_hotkey] <<'\n';
    if(game::toggle_mode[game::remove_flash_hotkey]) std::cout << "remove_flash: " << game::toggle_mode[game::remove_flash_hotkey] <<'\n';
    if (game::toggle_mode[game::bhop_hotkey]) std::cout << "bhop: " << game::toggle_mode[game::bhop_hotkey] <<'\n';
    if (game::toggle_mode[game::glow_esp_hotkey]) std::cout << "glow_esp: " << game::toggle_mode[game::glow_esp_hotkey] <<'\n';
    if (game::toggle_mode[game::radar_esp_hotkey]) std::cout << "radar_esp: " << game::toggle_mode[game::radar_esp_hotkey] <<'\n';
    if (game::toggle_mode[game::thirdperson_hotkey]) std::cout << "thirdperson: " << game::toggle_mode[game::thirdperson_hotkey] <<'\n';
    if (game::toggle_mode[game::desync_hotkey]) std::cout << "desync: " << game::toggle_mode[game::desync_hotkey] <<'\n';
    if (game::toggle_mode[game::aimbot_fire_hotkey]) std::cout << "aimbot: " << game::toggle_mode[game::aimbot_fire_hotkey] <<'\n';
    if (game::toggle_mode[game::aimbot_backtrack_hotkey]) std::cout << "backtrack: " << game::toggle_mode[game::aimbot_backtrack_hotkey] <<'\n';
    if (game::toggle_mode[game::global_target_hotkey]) std::cout << "global target: " << game::toggle_mode[game::global_target_hotkey] <<'\n';

    std::cout << std::endl;

    return 0;
}

int user_interface::CConnect([[maybe_unused]] std::stringstream& ss)
{
    memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);
    std::cout << "Reconnected" << std::endl;

    return 0;
}

int user_interface::CBuyAllPistols([[maybe_unused]] std::stringstream& ss)
{
    SendConsoleCommand("buy elite; buy hkp2000; buy usp_silencer; buy glock; buy p250; buy tec9; buy fn57; buy deagle");
    return 0;
}

int user_interface::CDropAll([[maybe_unused]] std::stringstream& ss)
{
    SendConsoleCommand("drop; drop; drop");

    return 0;
}

int user_interface::CUpdateVoice([[maybe_unused]] std::stringstream& ss)
{
    SendConsoleCommand("voice_inputfromfile 0; voice_recordtofile 0");

    std::remove("C:\\Users\\evanh\\works\\gaming\\steam\\steamapps\\common\\Counter-Strike Global Offensive\\voice_input.wav");
    int res = std::rename
    (
        "C:\\Users\\evanh\\works\\gaming\\steam\\steamapps\\common\\Counter-Strike Global Offensive\\voice_decompressed.wav",
        "C:\\Users\\evanh`\\works\\gaming\\steam\\steamapps\\common\\Counter-Strike Global Offensive\\voice_input.wav"
    );

    return res;
}

int user_interface::CRecordVoice([[maybe_unused]] std::stringstream& ss)
{
    SendConsoleCommand("voice_inputfromfile 0; voice_recordtofile 1");

    return 0;
}
int user_interface::CPlayVoice([[maybe_unused]] std::stringstream& ss)
{
    SendConsoleCommand("voice_recordtofile 0; voice_inputfromfile 1");

    return 0;
}
int user_interface::CExpose([[maybe_unused]] std::stringstream& ss)
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
                "say_team Enemy HP: " + std::to_string(game::player_entity_list[i].GetHealth()) +
                " Loc: " + location
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
int user_interface::CRecordPos(std::stringstream& ss)
{
    std::string file_name;
    ss >> file_name;

    std::ofstream file(file_name, std::ofstream::app);
    if (!file.is_open()) file.open(file_name, std::ofstream::trunc);

    file << game::player_entity_list[game::local_player_index].GetOrigin().x_ << ' '
        << game::player_entity_list[game::local_player_index].GetOrigin().y_ << ' '
        << game::player_entity_list[game::local_player_index].GetOrigin().z_ << '\n';

    file.close();

    return 0;
}
int user_interface::CGameConfig([[maybe_unused]] std::stringstream& ss)
{
    SendConsoleCommand("viewmodel_fov 68; viewmodel_offset_x 2.5; viewmodel_offset_y 2; viewmodel_offset_z -2; viewmodel_recoil 0; "
                       "cl_showpos 1; net_graph 1; +cl_show_team_equipment; cl_showfps 1");

    return 0;
}






int user_interface::CTest([[maybe_unused]] std::stringstream& ss)
{
    /*int a, b;
    ss >> a >> b;


    std::u8string message = u8"playerchatwheel . \"";

    for (int i = 1; i < 30; ++i)
    {
        if (i == 10 ) continue;
        char8_t color = i;
        message.push_back(color);

        std::string str = std::to_string(i);
        message.append(std::u8string(str.begin(), str.end()));
    }
    SendConsoleCommand(message);*/

    return 0;
}