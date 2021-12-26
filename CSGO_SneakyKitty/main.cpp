#include <iostream>
#include <thread>

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

#include "user_interface.h"
#include <string>

int main()
{
    std::cout << "Waiting for CSGO...\n";

    module::InitCSGOProcessHandle();

    do
    {
        module::client_dll = module::GetModuleBaseAddress("client.dll");
    } while (module::client_dll == NULL);

    do
    {
        module::engine_dll = module::GetModuleBaseAddress("engine.dll");
    } while (module::client_dll == NULL);

    std::cout << "Successfully obtained the process handle\n";


    std::cout << "Initializing weapon config tables...\n";
    weapon::InitIsGunTable();
    weapon::InitIsGrenadeTable();
    weapon::InitWeaponTypeTable();
    weapon::InitFOVTable();
    weapon::InitSmoothTable();
    std::cout << "Weapon config tables have loaded\n";


    //updating threads
    std::cout << "Launching info updating threads...\n";
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
    std::cout << "Client has updated the game info\n";


    //features threads
    std::cout << "Launching features threads...\n";
    std::thread fakelag_thd(Fakelag(), 16);
    std::thread remove_flash_thd(RemoveFlash(), 16);
    std::thread bhop_thd(Bhop(), 16);
    std::thread glow_esp_thd(GlowESP(), 16, 3.5f, Cham(255, 106, 0, 255));
    std::thread radar_esp_thd(RadarESP(), 32);
    std::thread thirdperson_thd(Thirdperson(), 1000);
    std::thread desync_thd(Desync(), 1, 33.0f);
    std::thread aimbot_thd(Aimbot(), 1);
    fakelag_thd.detach();
    remove_flash_thd.detach();
    bhop_thd.detach();
    glow_esp_thd.detach();
    radar_esp_thd.detach();
    thirdperson_thd.detach();
    desync_thd.detach();
    std::cout << "Cheats features have loaded\n";


    std::cout << "Initializing GUI...";
    std::thread GUI_thd(user_interface::GUI);
    GUI_thd.detach();
    std::cout << "User Interface has been created\n";

    std::cout << "Sneaky Kitty has loaded\nEnjoy your game!!!\n\a";

    HWND csgo_console = FindWindowA("Valve001", NULL);
    COPYDATASTRUCT message;
    message.dwData = 0;

    std::string command;
    while (true)
    {
        std::cout << ">> ";
        std::getline(std::cin, command);

        message.cbData = strlen(command.c_str()) + 1;
        message.lpData = (void*)(command.c_str());
        SendMessageA(csgo_console, WM_COPYDATA, 0, reinterpret_cast<LPARAM>(&message));
    }

}
