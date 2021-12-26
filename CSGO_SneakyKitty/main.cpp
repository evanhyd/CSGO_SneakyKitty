#include <iostream>
#include <thread>

#include "game.h"
#include "module.h"
#include "weapon.h"

#include "UpdateClientInfo.h"
#include "UpdateEntityInfo.h"
#include "UpdateBoneMatrixInfo.h"
#include "UpdateWeaponInfo.h"

#include "RemoveFlash.h"
#include "Bhop.h"
#include "Fakelag.h"
#include "GlowESP.h"
#include "RadarESP.h"
#include "Thirdperson.h"
#include "Desync.h"
#include "Aimbot.h"

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

    update_client_info_thd.detach();
    update_entity_info_thd.detach();
    update_bone_matrix_info_thd.detach();
    update_weapon_info_thd.detach();
    std::cout << "Info updating threads have detached\n";


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
    std::cout << "Features threads have detached\n";
    std::cout << "Sneaky Kitty has loaded\nEnjoy your game!!!\n\a";

    /*
    [ aimbot mode  ] backtrack  \ global target

    */

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
                game::toggle_mode[game::aimbot_backtrack_hotkey] ^= 1;
                if (game::toggle_mode[game::aimbot_backtrack_hotkey]) std::cout << '\a';
            }
        }
        else if (GetAsyncKeyState(game::global_target_hotkey))
        {
            game::toggle_mode[game::global_target_hotkey] ^= 1;
            if (game::toggle_mode[game::global_target_hotkey]) std::cout << '\a';
        }

        Sleep(500);
    }

}
