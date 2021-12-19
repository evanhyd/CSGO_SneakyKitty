#include "weapon.h"
#include <algorithm>


bool weapon::kIsGunTable[kWeaponNum] = {false};
int weapon::kConfigTypeTable[kWeaponNum] = { 0 };
float weapon::kFOVTable[kConfigNum] = { 0 };
float weapon::kSmoothTable[kConfigNum] = { 0 };

void weapon::InitIsGunTable()
{
	std::fill_n(kIsGunTable, kWeaponNum, true);
	kIsGunTable[0] = false;
	kIsGunTable[5] = false;
	kIsGunTable[6] = false;
	kIsGunTable[12] = false;
	kIsGunTable[15] = false;
	kIsGunTable[18] = false;
	kIsGunTable[20] = false;
	kIsGunTable[21] = false;
	kIsGunTable[22] = false;
	kIsGunTable[WEAPON_SHIELD] = false;
	kIsGunTable[WEAPON_KNIFEGG] = false;
	kIsGunTable[WEAPON_KNIFE] = false;
	kIsGunTable[WEAPON_FLASHBANG] = false;
    kIsGunTable[WEAPON_HEGRENADE] = false;
    kIsGunTable[WEAPON_SMOKEGRENADE] = false;
    kIsGunTable[WEAPON_MOLOTOV] = false;
    kIsGunTable[WEAPON_DECOY] = false;
	kIsGunTable[WEAPON_INCGRENADE] = false;
	kIsGunTable[WEAPON_C4] = false;
	kIsGunTable[50] = false;
	kIsGunTable[51] = false;
	kIsGunTable[52] = false;
	kIsGunTable[53] = false;
	kIsGunTable[54] = false;
	kIsGunTable[55] = false;
	kIsGunTable[56] = false;
	kIsGunTable[57] = false;
	kIsGunTable[58] = false;
	kIsGunTable[59] = false;
	kIsGunTable[62] = false;
}

void weapon::InitConfigTypeTable()
{
	std::fill_n(kConfigTypeTable, kWeaponNum, kNonWeapon);

	//pistol
	kConfigTypeTable[WEAPON_DEAGLE] = kPistol;
	kConfigTypeTable[WEAPON_ELITE] = kPistol;
	kConfigTypeTable[WEAPON_FIVESEVEN] = kPistol;
	kConfigTypeTable[WEAPON_GLOCK] = kPistol;
	kConfigTypeTable[WEAPON_TEC9] = kPistol;
	kConfigTypeTable[WEAPON_HKP2000] = kPistol;
	kConfigTypeTable[WEAPON_P250] = kPistol;
	kConfigTypeTable[WEAPON_USP_SILENCER] = kPistol;
	kConfigTypeTable[WEAPON_REVOLVER] = kPistol;


	//shotgun
	kConfigTypeTable[WEAPON_XM1014] = kShotgun;
	kConfigTypeTable[WEAPON_MAG7] = kShotgun;
	kConfigTypeTable[WEAPON_SAWEDOFF] = kShotgun;
	kConfigTypeTable[WEAPON_NOVA] = kShotgun;


	//SMG
	kConfigTypeTable[WEAPON_MAC10] = kSMG;
	kConfigTypeTable[WEAPON_P90] = kSMG;
	kConfigTypeTable[WEAPON_MP5] = kSMG;
	kConfigTypeTable[WEAPON_UMP45] = kSMG;
	kConfigTypeTable[WEAPON_BIZON] = kSMG;
	kConfigTypeTable[WEAPON_MP7] = kSMG;
	kConfigTypeTable[WEAPON_MP9] = kSMG;


	//assault rifle
	kConfigTypeTable[WEAPON_AK47] = kAssaultRifle;
	kConfigTypeTable[WEAPON_FAMAS] = kAssaultRifle;
	kConfigTypeTable[WEAPON_GALILAR] = kAssaultRifle;
	kConfigTypeTable[WEAPON_SCAR20] = kAssaultRifle;
	kConfigTypeTable[WEAPON_M4A1_SILENCER] = kAssaultRifle;
	kConfigTypeTable[WEAPON_AUG] = kAssaultRifle;
	kConfigTypeTable[WEAPON_G3SG1] = kAssaultRifle;
	kConfigTypeTable[WEAPON_M4A1] = kAssaultRifle;
	kConfigTypeTable[WEAPON_SG556] = kAssaultRifle;
	kConfigTypeTable[WEAPON_CZ75A] = kAssaultRifle;


	//sniper rifle
	kConfigTypeTable[WEAPON_AWP] = kSniperRifle;
	kConfigTypeTable[WEAPON_SSG08] = kSniperRifle;



	//machinegun
	kConfigTypeTable[WEAPON_NEGEV] = kMachinegun;
	kConfigTypeTable[WEAPON_M249] = kMachinegun;
}



void weapon::InitFOVTable()
{
	kFOVTable[kNonWeapon] = 1000.0f;
	kFOVTable[kPistol] = 1.6f;
	kFOVTable[kShotgun] = 2.0f;
	kFOVTable[kSMG] = 1.7f;
	kFOVTable[kAssaultRifle] = 1.6f;
	kFOVTable[kSniperRifle] = 2.0f;
	kFOVTable[kMachinegun] = 1.5f;
}

void weapon::InitSmoothTable()
{
	kSmoothTable[kNonWeapon] = 170.0f;
	kSmoothTable[kPistol] = 2.0f;
	kSmoothTable[kShotgun] = 4.0f;
	kSmoothTable[kSMG] = 4.0f;
	kSmoothTable[kAssaultRifle] = 3.5f;
	kSmoothTable[kSniperRifle] = 1.0f;
	kSmoothTable[kMachinegun] = 4.0f;
}

//int weapon::current_weapon_entity_index = weapon::DefinitionIndex::WEAPON_INVALID;
//DWORD weapon::current_weapon_entity_address = NULL;
//short weapon::current_weapon_def_index = weapon::DefinitionIndex::WEAPON_INVALID;


//void weapon::WeaponUpdate()
//{
//	while (true)
//	{
//		if (client::connection_status != client::ConnectionState::FULLY_CONNECTED)
//		{
//			Sleep(3000);
//			continue;
//		}
//
//		rM(PlayerEntity::local_player + m_hActiveWeapon, weapon::current_weapon_entity_index);
//		//only keep the first 3 bytes
//		weapon::current_weapon_entity_index &= 0xFFF;
//
//		//note: this is entity, so we may be anble to render it
//		rM(module::client_dll + dwEntityList + (weapon::current_weapon_entity_index - 1) * 0x10, weapon::current_weapon_entity_address);
//
//		rM(weapon::current_weapon_entity_address + m_iItemDefinitionIndex, weapon::current_weapon_def_index);
//
//		this_thread::sleep_for(chrono::milliseconds(8));
//	}
//}