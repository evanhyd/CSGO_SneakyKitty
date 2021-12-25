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
    weapon::InitConfigTypeTable();
    weapon::InitFOVTable();
    weapon::InitSmoothTable();
    std::cout << "Weapon config tables have loaded\n";


    //updating threads
    std::cout << "Launching info updating threads...\n";
    std::thread UpdateClientInfoThread(UpdateClientInfo(), 5000);
    std::thread UpdateEntityInfo(UpdateEntityInfo(), 1);
    std::thread UpdateBoneMatrixInfoThread(UpdateBoneMatrixInfo(), 1);
    std::thread UpdateWeaponInfo(UpdateWeaponInfo(), 8);

    UpdateClientInfoThread.detach();
    UpdateEntityInfo.detach();
    UpdateBoneMatrixInfoThread.detach();
    UpdateWeaponInfo.detach();
    std::cout << "Info updating threads have detached\n";


    //features threads
    std::cout << "Launching features threads...\n";
    std::thread FakelagThread(Fakelag(), 16);
    std::thread RemoveFlashThread(RemoveFlash(), 16);
    std::thread BhopThread(Bhop(), 16);
    std::thread GlowThread(GlowESP(), 16);
    FakelagThread.detach();
    RemoveFlashThread.detach();
    BhopThread.detach();
    GlowThread.detach();
    std::cout << "Features threads have detached\n";
    std::cout << "Sneaky Kitty has loaded\nEnjoy your game!!!\n\a";

    /*
    
    F10 Radar
    - third person  + desync
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

        Sleep(500);
    }


    //UpdateClientInfoThread.

    /*
    
    load gui

    loop:
        update connection status: //done

            if in game:
                thd: update basic client info (local_player_index, client_state, net_channel, tick rate, curr tick) //done
                thd: update player entity address array //done

                thd: update player entity info array  //done
                thd: update player bone matrix array //done
                thd: update player weapon info //done

                thd: update player input info


                thd: check hotkey activation
                         toggle cheat features

        
            else:
                turn off all the features
    
    */
}
