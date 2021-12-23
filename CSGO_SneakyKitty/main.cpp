#include "module.h"
#include <iostream>


#include "Angle.h"
#include "BoneMatrix.h"
#include "Cham.h"
#include "Position.h"
#include "Vector3.h"
#include "weapon.h"

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



    /*
    
    load gui

    loop:
        update connection status:

            if in game:
                thd: update basic client info (local_player_index, client_state, net_channel, tick rate, curr tick)
                thd: update player entity address array

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
