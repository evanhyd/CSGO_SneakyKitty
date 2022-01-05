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

std::unordered_map <std::string, char8_t> user_interface::chat_color_map;
std::vector<std::u8string> user_interface::skin_lists[5] = {};
std::unordered_map <std::string, std::function<int(std::stringstream&)>> user_interface::command_map;

void user_interface::InitUserInterface()
{
    chat_color_map.insert({ "@null", kNull });
    chat_color_map.insert({ "@white", kWhite });
    chat_color_map.insert({ "@red", kRed });
    chat_color_map.insert({ "@light_yellow", kLightYellow });
    chat_color_map.insert({ "@green", kGreen });
    chat_color_map.insert({ "@light_green", kLightGreen });
    chat_color_map.insert({ "@medium_green", kMediumGreen });
    chat_color_map.insert({ "@medium_red", kMediumRed });
    chat_color_map.insert({ "@grey", kGrey });
    chat_color_map.insert({ "@yellow", kYellow });
    chat_color_map.insert({ "@light_blue", kLightBlue });
    chat_color_map.insert({ "@blue", kBlue });
    chat_color_map.insert({ "@light_grey", kLightGrey });
    chat_color_map.insert({ "@pink", kPink });
    chat_color_map.insert({ "@light_red", kLightRed });
    chat_color_map.insert({ "@gold", kGold });






    srand(time(NULL));
    //Operation Riptide Case
    skin_lists[kCommon].push_back(u8"AUG | Plague");
    skin_lists[kCommon].push_back(u8"Dual Berettas | Tread");
    skin_lists[kCommon].push_back(u8"G3SG1 | Keeping Tabs");
    skin_lists[kCommon].push_back(u8"MP7 | Guerrilla");
    skin_lists[kCommon].push_back(u8"PP-Bizon | Lumen");
    skin_lists[kCommon].push_back(u8"USP-S | Black Lotus");
    skin_lists[kCommon].push_back(u8"XM1014 | Watchdog");

    skin_lists[kRare].push_back(u8"MAG-7 | BI83 Spectrum");
    skin_lists[kRare].push_back(u8"FAMAS | ZX Spectron");
    skin_lists[kRare].push_back(u8"Five-SeveN | Boost Protocol");
    skin_lists[kRare].push_back(u8"MP9 | Mount Fuji");
    skin_lists[kRare].push_back(u8"M4A4 | Spider Lily");

    skin_lists[kEpic].push_back(u8"MAC-10 | Toybox");
    skin_lists[kEpic].push_back(u8"Glock-18 | Snack Attack");
    skin_lists[kEpic].push_back(u8"SSG 08 | Turbo Peek");

    skin_lists[kLegendary].push_back(u8"AK-47 | Leet Museo");
    skin_lists[kMythic].push_back(u8"Desert Eagle | Ocean Drive");


    //Operation Snakebite Case
    skin_lists[kCommon].push_back(u8"SG 553 | Heavy Metal");
    skin_lists[kCommon].push_back(u8"Glock-18 | Clear Polymer");
    skin_lists[kCommon].push_back(u8"M249 | O.S.I.P.R.");
    skin_lists[kCommon].push_back(u8"MP7 | Guerrilla");
    skin_lists[kCommon].push_back(u8"CZ75-Auto | Circaetus");
    skin_lists[kCommon].push_back(u8"UMP-45 | Oscillator");
    skin_lists[kCommon].push_back(u8"R8 Revolver | Junk Yard");
    skin_lists[kCommon].push_back(u8"Nova | Windblown");

    skin_lists[kRare].push_back(u8"P250 | Cyber Shell");
    skin_lists[kRare].push_back(u8"Negev | dev_texture");
    skin_lists[kRare].push_back(u8"MAC-10 | Button Masher");
    skin_lists[kRare].push_back(u8"Desert Eagle | Trigger Discipline");
    skin_lists[kRare].push_back(u8"AK-47 | Slate");

    skin_lists[kEpic].push_back(u8"MP9 | Food Chain");
    skin_lists[kEpic].push_back(u8"XM1014 | XOXO");
    skin_lists[kEpic].push_back(u8"Galil AR | Chromatic Aberration");

    skin_lists[kLegendary].push_back(u8"USP-S | The Traitor");
    skin_lists[kLegendary].push_back(u8"M4A4 | In Living Color");

    skin_lists[kMythic].push_back(u8"★ Karambit | Lore");



    //Operation Broken Fang Case
    skin_lists[kCommon].push_back(u8"G3SG1 | Digital Mesh");
    skin_lists[kCommon].push_back(u8"CZ75-Auto | Vendetta");
    skin_lists[kCommon].push_back(u8"P90 | Cocoa Rampage");
    skin_lists[kCommon].push_back(u8"M249 | Deep Relief");
    skin_lists[kCommon].push_back(u8"Galil AR | Vandal");
    skin_lists[kCommon].push_back(u8"MP5-SD | Condition Zero");
    skin_lists[kCommon].push_back(u8"P250 | Contaminant");

    skin_lists[kRare].push_back(u8"Dual Berettas | Dezastre");
    skin_lists[kRare].push_back(u8"Nova | Clear Polymer");
    skin_lists[kRare].push_back(u8"UMP-45 | Gold Bismuth");
    skin_lists[kRare].push_back(u8"SSG 08 | Parallax");
    skin_lists[kRare].push_back(u8"AWP | Exoskeleton");

    skin_lists[kEpic].push_back(u8"M4A4 | Cyber Security");
    skin_lists[kEpic].push_back(u8"Five-SeveN | Fairy Tale");
    skin_lists[kEpic].push_back(u8"USP-S | Monster Mashup");

    skin_lists[kLegendary].push_back(u8"Glock-18 | Neo-Noir");
    skin_lists[kLegendary].push_back(u8"M4A1-S | Printstream");



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
    command_map.insert({ "in_game_config", CInGameConfig });
    command_map.insert({ "radio", CRadio });
    command_map.insert({ "fake_ban", CFakeBan });
    command_map.insert({ "fake_unbox", CFakeUnbox});


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
        if (word[0] == '@')
        {
            auto iter = chat_color_map.find(word);
            if (iter != chat_color_map.end()) radio_message.push_back(iter->second);
            else if (word == "@new_line")  radio_message.append(kNewLine);
            else return 1;
        }
        else radio_message += std::u8string(word.begin(), word.end()) + u8" ";
    }

    SendConsoleCommand(radio_message);

    return 0;
}



int user_interface::CFakeBan(std::stringstream& ss)
{
    std::string player_name;
    ss >> player_name;

    std::u8string fake_ban_message = u8"playerchatwheel . \"In position";
    fake_ban_message.append(kNewLine);
    fake_ban_message.push_back(ChatColor::kRed);
    fake_ban_message.append(std::u8string(player_name.begin(), player_name.end()) + u8" has been permanently banned from official CS:GO servers.\"");


    SendConsoleCommand(fake_ban_message);

    return 0;
}
int user_interface::CFakeUnbox(std::stringstream& ss)
{
    std::u8string fake_unbox_message = u8"playerchatwheel . \"In position";
    fake_unbox_message.append(kNewLine);
    fake_unbox_message.push_back(ChatColor::kLightYellow);

    std::string word;

    //player name
    ss >> word;
    fake_unbox_message.append(std::u8string(word.begin(), word.end()));
    fake_unbox_message.push_back(ChatColor::kWhite);
    fake_unbox_message.append(u8" has opened a container and found: ");


    float rng = static_cast<float>(rand()) / RAND_MAX;

    int rarity_index;
    char8_t rarity_color;

    if (rng > 0.9974f)
    {
        rarity_index = kMythic;
        rarity_color = kYellow;
    }
    else if (rng > 0.9936f)
    {
        rarity_index = kLegendary;
        rarity_color = kRed;
    }
    else if (rng > 0.968f)
    {
        rarity_index = kEpic;
        rarity_color = kPink;
    }
    else if (rng > 0.8402f)
    {
        rarity_index = kRare;
        rarity_color = kBlue;
    }
    else
    {
        rarity_index = kCommon;
        rarity_color = kLightBlue;
    }

    int skin_index = rand() % skin_lists[rarity_index].size();
    fake_unbox_message.push_back(rarity_color);
    fake_unbox_message.append(skin_lists[rarity_index][skin_index]);

    SendConsoleCommand(fake_unbox_message);

    return 0;
}























int user_interface::CTest(std::stringstream& ss)
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