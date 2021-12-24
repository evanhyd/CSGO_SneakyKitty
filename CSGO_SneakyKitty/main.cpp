#include <iostream>
#include <thread>

#include "module.h"
#include "weapon.h"
#include "UpdateClientInfo.h"

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


    std::cout << "Initializing weapon config tables\n";
    weapon::InitIsGunTable();
    weapon::InitConfigTypeTable();
    weapon::InitFOVTable();
    weapon::InitSmoothTable();
    std::cout << "Weapon config tables have loaded\n";



    std::thread UpdateClientInfoThread(UpdateClientInfo(), 5000);


    while (true)
    {
        Sleep(10000);
    }
    //UpdateClientInfoThread.

    /*
    
    load gui

    loop:
        update connection status: //done

            if in game:
                thd: update basic client info (local_player_index, client_state, net_channel, tick rate, curr tick) //done
                thd: update player entity address array //done

                thd: update player entity info array 
                thd: update player bone matrix array
                thd: update player weapon info
                thd: update player input info


                thd: check hotkey activation
                         toggle cheat features

        
            else:
                turn off all the features
    
    */
}
