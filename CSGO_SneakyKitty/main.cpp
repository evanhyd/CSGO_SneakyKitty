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





    Angle a(1.0f, 1.0f);
    BoneMatrix b;
    constexpr Cham c(1, 1, 1, 1);
    Position p(1.0f, 1.0f, 1.0f);
    Vector3 v(1.0f, 1.0f, 1.0f);
}
