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
    command_map.insert({ "set_angle", CSetAngle});
    command_map.insert({ "record_pos", CRecordPos });
    command_map.insert({ "in_game_config", CInGameConfig });
    command_map.insert({ "radio", CRadio });


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


int user_interface::CHelp(std::stringstream& ss)
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
    std::cout << "/connect (fix the connection issue)\n";
    std::cout << "/record voice (K to record)\n";
    std::cout << "/update voice\n";
    std::cout << "/play voice (K to play)\n";
    std::cout << "/expose\n";
    std::cout << "/set angle [pitch/yaw/roll] [angle in degree]\n";

    std::cout << std::endl;

    return 0;
}

int user_interface::CStatus(std::stringstream& ss)
{
    std::cout << "Toggle Status\n";
    std::cout << "fakelag: " << game::toggle_mode[game::fakelag_hotkey] <<'\n';
    std::cout << "remove_flash: " << game::toggle_mode[game::remove_flash_hotkey] <<'\n';
    std::cout << "bhop: " << game::toggle_mode[game::bhop_hotkey] <<'\n';
    std::cout << "glow_esp: " << game::toggle_mode[game::glow_esp_hotkey] <<'\n';
    std::cout << "radar_esp: " << game::toggle_mode[game::radar_esp_hotkey] <<'\n';
    std::cout << "thirdperson: " << game::toggle_mode[game::thirdperson_hotkey] <<'\n';
    std::cout << "desync: " << game::toggle_mode[game::desync_hotkey] <<'\n';
    std::cout << "aimbot: " << game::toggle_mode[game::aimbot_fire_hotkey] <<'\n';
    std::cout << "backtrack: " << game::toggle_mode[game::aimbot_backtrack_hotkey] <<'\n';
    std::cout << "global target: " << game::toggle_mode[game::global_target_hotkey] <<'\n';

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
    SendConsoleCommand("buy elite; buy hkp2000; buy usp_silencer; buy glock; buy p250; buy tec9; buy fn57; buy deagle");
    return 0;
}

int user_interface::CDropAll(std::stringstream& ss)
{
    SendConsoleCommand("drop; drop");

    return 0;
}

int user_interface::CUpdateVoice(std::stringstream& ss)
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

int user_interface::CRecordVoice(std::stringstream& ss)
{
    SendConsoleCommand("voice_inputfromfile 0; voice_recordtofile 1");

    return 0;
}
int user_interface::CPlayVoice(std::stringstream& ss)
{
    SendConsoleCommand("voice_recordtofile 0; voice_inputfromfile 1");

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
int user_interface::CInGameConfig(std::stringstream& ss)
{
    SendConsoleCommand("viewmodel_fov 68; viewmodel_offset_x 0; viewmodel_offset_y 2; viewmodel_offset_z -2; viewmodel_recoil 0; cl_showpos 1; net_graph 1");

    return 0;
}
int user_interface::CRadio(std::stringstream& ss)
{
    std::u8string radio_message = u8"playerchatwheel . \"";
    std::string word;

    while (ss >> word)
    {
        //just in case
        if (word[0] == '@')
        {
            if (word == "@white") radio_message.push_back(kWhite);
            else if (word == "@red") radio_message.push_back(kRed);
            else if (word == "@blue") radio_message.push_back(kBlue);
            else if (word == "@green") radio_message.push_back(kGreen);
            else if (word == "@light_green") radio_message.push_back(kLightGreen);
            else if (word == "@medium_green") radio_message.push_back(kMediumGreen);
            else if (word == "@light_red") radio_message.push_back(kLightRed);
            else if (word == "@grey") radio_message.push_back(kGrey);
            else if (word == "@yellow") radio_message.push_back(kYellow);
            else if (word == "@medium_blue") radio_message.push_back(kMediumBlue);
            else if (word == "@dark_blue") radio_message.push_back(kDarkBlue);
            else if (word == "@medium_grey") radio_message.push_back(kMediumGrey);
            else if (word == "@purple") radio_message.push_back(kPurple);
            else if (word == "@medium_red") radio_message.push_back(kMediumRed);
            else if (word == "@gold") radio_message.push_back(kGold);
            else if (word == "@new_line") radio_message.append(kNewLine);
            else return 1;
        }
        else radio_message += std::u8string(word.begin(), word.end()) + u8" ";
    }

    SendConsoleCommand(radio_message);

    return 0;
}

int user_interface::CTest(std::stringstream& ss)
{
    std::u8string message = u8"say hel\x2029\x2029\x2029lo";
    SendConsoleCommand(message);

    return 0;
}