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
    command_map.insert({ "aimbot", HAimbot });
    command_map.insert({ "ragebot", HRagebot});
    command_map.insert({ "backtrack", HBacktrack});
    command_map.insert({ "global_target", HGlobalTarget });
    command_map.insert({ "bomb_timer", HBombTimer });


    command_map.insert({ "help", CHelp });
    command_map.insert({ "status", CStatus});
    command_map.insert({ "connect", CConnect });
    command_map.insert({ "buy_all_pistols", CBuyAllPistols});
    command_map.insert({ "drop_all", CDrop});
    command_map.insert({ "update_voice", CUpdateVoice});
    command_map.insert({ "record_voice", CRecordVoice});
    command_map.insert({ "play_voice", CPlayVoice});
    command_map.insert({ "expose", CExpose});
    command_map.insert({ "set_angle", CSetAngle});
    command_map.insert({ "record_pos", CRecordPos });
    command_map.insert({ "pro_config", CProConfig });
    command_map.insert({ "troll_config", CTrollConfig });
    command_map.insert({ "quit", CQuit });
    

    command_map.insert({ "test", CTest });
}



void user_interface::SendConsoleCommand(const std::string& command_line)
{
    COPYDATASTRUCT message{};
    message.dwData = 0;
    message.lpData = (void*)(command_line.c_str());
    message.cbData = command_line.size() + 1;
    SendMessageA(module::csgo_console_window, WM_COPYDATA, 0, reinterpret_cast<LPARAM>(&message));
}
void user_interface::SendConsoleCommand(const std::u8string& command_line)
{
    COPYDATASTRUCT message{};
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


    //incompatiable with backtrack/desync/ragebot
    if (toggle_mode[kBacktrack] || toggle_mode[kDesync] || toggle_mode[kRagebot]) return 1;

    if (mode != 0) std::cout << '\a';
    toggle_mode[kFakelag] = mode;

    return 0;
}
int user_interface::HRemoveFlash(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    toggle_mode[kRemoveFlash] = mode;

    return 0;
}
int user_interface::HBhop(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    toggle_mode[kBhop] = mode;

    return 0;
}
int user_interface::HGlowESP(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(4));

    if (mode != 0) std::cout << '\a';
    toggle_mode[kGlowESP] = mode;

    return 0;
}
int user_interface::HRadarESP(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    toggle_mode[kRadarESP] = mode;

    return 0;
}
int user_interface::HThirdperson(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    toggle_mode[kThirdperson] = mode;

    return 0;
}
int user_interface::HDesync(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));


    //incompatiable with fakelag/backtrack/ragebot
    if (toggle_mode[kFakelag] || toggle_mode[kBacktrack] || toggle_mode[kRagebot]) return 1;

    if (mode != 0) std::cout << '\a';
    toggle_mode[kDesync] = mode;

    return 0;
}
int user_interface::HAimbot(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(2));

    //incompatiable with ragebot/backtrack (aimbot mode 2)
    if (toggle_mode[kBacktrack] || toggle_mode[kRagebot]) return 1;

    if (mode != 0) std::cout << '\a';
    toggle_mode[kAimbot] = mode;

    return 0;
}
int user_interface::HRagebot(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(3));

    //incompatiable with fakelag/backtrack/desync/aimbot
    if (toggle_mode[kFakelag] || toggle_mode[kBacktrack] || toggle_mode[kDesync] || toggle_mode[kAimbot]) return 1;


    if (mode != 0) std::cout << '\a';
    toggle_mode[kRagebot] = mode;

    return 0;
}
int user_interface::HBacktrack(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    //incompatiable with fakelag/desync/ragebot
    if (toggle_mode[kFakelag] || toggle_mode[kDesync] || toggle_mode[kRagebot]) return 1;

    //require aimbot
    if (toggle_mode[kAimbot] == 0) return 0;

    if (mode != 0)
    {
        SendConsoleCommand("unbind mouse1");
        std::cout << '\a';
    }
    else
    {
        SendConsoleCommand("bind mouse1 +attack");
    }
    toggle_mode[kBacktrack] = mode;

    return 0;
}
int user_interface::HGlobalTarget(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    user_interface::toggle_mode[kGlobalTarget] = mode;

    return 0;
}
int user_interface::HBombTimer(std::stringstream& ss)
{
    short mode;
    ss >> mode;
    mode = std::clamp(mode, short(0), short(1));

    if (mode != 0) std::cout << '\a';
    user_interface::toggle_mode[kBombTimer] = mode;

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
    std::cout << "/aimbot(legit, rage)\n";
    std::cout << "/backtrack(requires aimbot)\n";
    std::cout << "/ragebot\n";
    std::cout << "/global target\n";
    std::cout << "/bomb timer\n";


    std::cout << "\n\nBuilt-in commands:\n";
    std::cout << "/help\n";
    std::cout << "/status\n";
    std::cout << "/pro_config\n";
    std::cout << "/troll_config\n";
    std::cout << "/connect (fix the connection issue)\n";

    std::cout << "/record voice (K to record)\n";
    std::cout << "/update voice\n";
    std::cout << "/play voice (K to play)\n";

    std::cout << "/record_pos\n";
    std::cout << "/expose\n";
    std::cout << "/set_angle [pitch/yaw/roll] [angle in degree]\n";
    std::cout << "/buy_all_pistols\n";
    std::cout << "/drop\n";

    std::cout << std::endl;

    return 0;
}

int user_interface::CStatus([[maybe_unused]] std::stringstream& ss)
{
    std::cout << "Toggle Status\n";

    if (toggle_mode[kFakelag])      std::cout << "fakelag: " << toggle_mode[kFakelag] <<'\n';
    if (toggle_mode[kRemoveFlash])  std::cout << "remove_flash: " << toggle_mode[kRemoveFlash] <<'\n';
    if (toggle_mode[kBhop])         std::cout << "bhop: " << toggle_mode[kBhop] <<'\n';
    if (toggle_mode[kGlowESP])      std::cout << "glow_esp: " << toggle_mode[kGlowESP] <<'\n';
    if (toggle_mode[kRadarESP])     std::cout << "radar_esp: " << toggle_mode[kRadarESP] <<'\n';
    if (toggle_mode[kThirdperson])  std::cout << "thirdperson: " << toggle_mode[kThirdperson] <<'\n';
    if (toggle_mode[kDesync])       std::cout << "desync: " << toggle_mode[kDesync] <<'\n';
    if (toggle_mode[kAimbot])       std::cout << "aimbot: " << toggle_mode[kAimbot] <<'\n';
    if (toggle_mode[kBacktrack])    std::cout << "backtrack: " << toggle_mode[kBacktrack] << '\n';
    if (toggle_mode[kRagebot])      std::cout << "ragebot: " << toggle_mode[kRagebot] << '\n';
    if (toggle_mode[kGlobalTarget]) std::cout << "global target: " << toggle_mode[kGlobalTarget] << '\n';
    if (toggle_mode[kBombTimer])    std::cout << "bomb timer: " << toggle_mode[kBombTimer] << '\n';

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

int user_interface::CDrop([[maybe_unused]] std::stringstream& ss)
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
                "echo Enemy " + std::to_string(i) + " HP: " + std::to_string(game::player_entity_list[i].GetHealth()) + " at " + location
            );
            Sleep(500);
        }
    }

    return 0;
}
int user_interface::CSetAngle(std::stringstream& ss)
{
    Angle angle{};
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
int user_interface::CProConfig([[maybe_unused]] std::stringstream& ss)
{
    //view model
    SendConsoleCommand(R"(viewmodel_fov 68; viewmodel_offset_x 2.5; viewmodel_offset_y 2; viewmodel_offset_z -2; viewmodel_recoil 0)");
    Sleep(500);

    //crosshair
    SendConsoleCommand(R"(cl_crosshairstyle "4";cl_crosshaircolor "1";cl_crosshairsize "3";cl_crosshairgap "-5";cl_crosshairalpha "255";cl_crosshairusealpha "1";cl_crosshairthickness "0.2";cl_crosshair_drawoutline "1";cl_crosshair_outlinethickness "0";cl_crosshairdot "1";)");
    Sleep(500);
    SendConsoleCommand(R"(cl_crosshair_t "0";cl_crosshairgap_useweaponvalue "0";hud_showtargetid "1";)");
    Sleep(500);

    //keybind
    SendConsoleCommand(R"(bind space +jump; bind mwheeldown +jump)");
    Sleep(500);

    //mouse sensitivity
    SendConsoleCommand(R"(sensitivity 7.0; m_rawinput 1; m_customaccel 0)");
    Sleep(500);

    //misc
    SendConsoleCommand(R"(cl_showpos 1; cl_showfps 1; net_graph 1; +cl_show_team_equipment; cl_autowepswitch 0)");
    return 0;
}


int user_interface::CTrollConfig([[maybe_unused]]std::stringstream& ss)
{
    //crosshair
    SendConsoleCommand(R"(cl_crosshairstyle "3";cl_crosshaircolor "5";cl_crosshairsize "100";cl_crosshairgap "0";cl_crosshairalpha "255";cl_crosshairusealpha "1";cl_crosshairthickness "100";cl_crosshaircolor_r "255";cl_crosshaircolor_g "255";cl_crosshaircolor_b "255";)");
    Sleep(500);

    SendConsoleCommand(R"(cl_crosshair_drawoutline "1";cl_crosshair_outlinethickness "3";cl_crosshairdot "1";cl_crosshair_t "0";cl_crosshairgap_useweaponvalue "0";hud_showtargetid "1";)");

    return 0;
}

int user_interface::CQuit([[maybe_unused]]std::stringstream& ss)
{
    std::fill_n(user_interface::toggle_mode, 255, short(0));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    exit(0);
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


short user_interface::toggle_mode[255] = {};