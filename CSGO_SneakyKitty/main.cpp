﻿#include <iostream>
#include <thread>
#include <string>

#include "game.h"
#include "module.h"
#include "weapon.h"

#include "UpdateClientInfo.h"
#include "UpdateEntityInfo.h"
#include "UpdateBoneMatrixInfo.h"
#include "UpdateWeaponInfo.h"
#include "UpdateInputInfo.h"

#include "RemoveFlash.h"
#include "Bhop.h"
#include "Fakelag.h"
#include "GlowESP.h"
#include "RadarESP.h"
#include "Thirdperson.h"
#include "Desync.h"
#include "Aimbot.h"
#include "Ragebot.h"
#include "BombTimer.h"

#include "user_interface.h"

int main()
{
//#define PASS_REQUIRED
#ifdef PASS_REQUIRED
    std::cout <<"Microsoft Windows [Version 10.0.19042.1415]\n(c)Microsoft Corporation.All rights reserved.\n";

    std::string pass;
    while (true)
    {
        std::cout << "\nC:\\Users\\Asd123**";
        std::cin >> pass;
        if (pass == "Asd123**") break;
    }
    system("cls");
#endif


    std::cout << "Fetching game resources...\n";
    offsets::UpdateOffsets();


    std::cout << "Waiting for CSGO...\n";

    module::InitCSGOProcessHandle();
    module::InitCSGOConsoleWindow();

    do
    {
        module::client_dll = module::GetModuleBaseAddress("client.dll");
    } while (module::client_dll == NULL);

    do
    {
        module::engine_dll = module::GetModuleBaseAddress("engine.dll");
    } while (module::client_dll == NULL);


    std::cout << "Initializing weapon configs...\n";
    weapon::InitIsGunTable();
    weapon::InitIsGrenadeTable();
    weapon::InitWeaponTypeTable();
    weapon::InitFOVTable();
    weapon::InitSmoothTable();


    //updating threads
    std::cout << "Initializing client info...\n";
    std::thread update_client_info_thd(UpdateClientInfo(), 5000);
    std::thread update_entity_info_thd(UpdateEntityInfo(), 1);
    std::thread update_bone_matrix_info_thd(UpdateBoneMatrixInfo(), 1);
    std::thread update_weapon_info_thd(UpdateWeaponInfo(), 16);
    std::thread update_input_info(UpdateInputInfo(), 1);

    update_client_info_thd.detach();
    update_entity_info_thd.detach();
    update_bone_matrix_info_thd.detach();
    update_weapon_info_thd.detach();
    update_input_info.detach();


    //features threads
    std::cout << "Initializing features...\n";
    std::thread fakelag_thd(Fakelag(), 16);
    std::thread remove_flash_thd(RemoveFlash(), 16);
    std::thread bhop_thd(Bhop(), 16);
    std::thread glow_esp_thd(GlowESP(), 16, 1.5f, Cham(255, 106, 0, 255));
    std::thread radar_esp_thd(RadarESP(), 32);
    std::thread thirdperson_thd(Thirdperson(), 1000);
    std::thread desync_thd(Desync(), 1);
    std::thread aimbot_thd(Aimbot(), 1);
    std::thread ragebot_thd(Ragebot(), 1);
    std::thread bomb_timer_thd(BombTimer(), 16);
    fakelag_thd.detach();
    remove_flash_thd.detach();
    bhop_thd.detach();
    glow_esp_thd.detach();
    radar_esp_thd.detach();
    thirdperson_thd.detach();
    desync_thd.detach();
    ragebot_thd.detach();
    bomb_timer_thd.detach();

    std::cout << "Initializing GUI...";
    user_interface::InitUserInterface();

    std::cout << "Sneaky Kitty has loaded\nEnjoy your game!!!\n\a";

    std::string command;
    while (true)
    {
        try
        {
            std::cout << ">> ";
            std::getline(std::cin, command);

            if (command[0] == '?') user_interface::SendConsoleCommand(command.substr(1));
            else if (command[0] == '/') user_interface::SendBuiltInCommand(command.substr(1));
            else std::cout << "Invalid Prefix\a"<<std::endl;

        }
        catch (std::exception& error)
        {
            std::cerr << error.what() << '\n';
        }
    }

}
