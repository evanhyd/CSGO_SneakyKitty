#include "weapon.h"
#include <algorithm>


bool weapon::kIsGunTable[kMaxWeaponNum] = {};
bool weapon::kIsGrenadeTable[kMaxWeaponNum] = {};
int weapon::kWeaponTypeTable[kMaxWeaponNum] = {};
float weapon::kFOVTable[kMaxWeaponTypeNum] = {};
float weapon::kSmoothTable[kMaxWeaponTypeNum] = {};

bool weapon::IsC4(short weapon_def_index)
{
	return weapon_def_index == WEAPON_C4;
}
bool weapon::IsGun(short weapon_def_index)
{
	return kIsGunTable[weapon_def_index];
}
bool weapon::IsGrenade(short weapon_def_index)
{
	return kIsGrenadeTable[weapon_def_index];
}
int weapon::GetWeaponType(short weapon_def_index)
{
	return kWeaponTypeTable[weapon_def_index];
}
float weapon::GetFOV(short weapon_def_index)
{
	return kFOVTable[kWeaponTypeTable[weapon_def_index]];
}
float weapon::GetSmooth(short weapon_def_index)
{
	return kSmoothTable[kWeaponTypeTable[weapon_def_index]];
}

void weapon::InitIsGunTable()
{
	std::fill_n(kIsGunTable, kMaxWeaponNum, true);
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


void weapon::InitIsGrenadeTable()
{
	std::fill_n(kIsGrenadeTable, kMaxWeaponNum, false);
	kIsGrenadeTable[WEAPON_FLASHBANG] = true;
	kIsGrenadeTable[WEAPON_HEGRENADE] = true;
	kIsGrenadeTable[WEAPON_SMOKEGRENADE] = true;
	kIsGrenadeTable[WEAPON_MOLOTOV] = true;
	kIsGrenadeTable[WEAPON_DECOY] = true;
	kIsGrenadeTable[WEAPON_INCGRENADE] = true;
}

void weapon::InitWeaponTypeTable()
{
	std::fill_n(kWeaponTypeTable, kMaxWeaponNum, kNonWeapon);

	//pistol
	kWeaponTypeTable[WEAPON_DEAGLE] = kPistol;
	kWeaponTypeTable[WEAPON_ELITE] = kPistol;
	kWeaponTypeTable[WEAPON_FIVESEVEN] = kPistol;
	kWeaponTypeTable[WEAPON_GLOCK] = kPistol;
	kWeaponTypeTable[WEAPON_TEC9] = kPistol;
	kWeaponTypeTable[WEAPON_HKP2000] = kPistol;
	kWeaponTypeTable[WEAPON_P250] = kPistol;
	kWeaponTypeTable[WEAPON_USP_SILENCER] = kPistol;
	kWeaponTypeTable[WEAPON_REVOLVER] = kPistol;


	//shotgun
	kWeaponTypeTable[WEAPON_XM1014] = kShotgun;
	kWeaponTypeTable[WEAPON_MAG7] = kShotgun;
	kWeaponTypeTable[WEAPON_SAWEDOFF] = kShotgun;
	kWeaponTypeTable[WEAPON_NOVA] = kShotgun;


	//SMG
	kWeaponTypeTable[WEAPON_MAC10] = kSMG;
	kWeaponTypeTable[WEAPON_P90] = kSMG;
	kWeaponTypeTable[WEAPON_MP5] = kSMG;
	kWeaponTypeTable[WEAPON_UMP45] = kSMG;
	kWeaponTypeTable[WEAPON_BIZON] = kSMG;
	kWeaponTypeTable[WEAPON_MP7] = kSMG;
	kWeaponTypeTable[WEAPON_MP9] = kSMG;


	//assault rifle
	kWeaponTypeTable[WEAPON_AK47] = kAssaultRifle;
	kWeaponTypeTable[WEAPON_FAMAS] = kAssaultRifle;
	kWeaponTypeTable[WEAPON_GALILAR] = kAssaultRifle;
	kWeaponTypeTable[WEAPON_SCAR20] = kAssaultRifle;
	kWeaponTypeTable[WEAPON_M4A1_SILENCER] = kAssaultRifle;
	kWeaponTypeTable[WEAPON_AUG] = kAssaultRifle;
	kWeaponTypeTable[WEAPON_G3SG1] = kAssaultRifle;
	kWeaponTypeTable[WEAPON_M4A1] = kAssaultRifle;
	kWeaponTypeTable[WEAPON_SG556] = kAssaultRifle;
	kWeaponTypeTable[WEAPON_CZ75A] = kAssaultRifle;


	//sniper rifle
	kWeaponTypeTable[WEAPON_AWP] = kSniperRifle;
	kWeaponTypeTable[WEAPON_SSG08] = kSniperRifle;



	//machinegun
	kWeaponTypeTable[WEAPON_NEGEV] = kMachinegun;
	kWeaponTypeTable[WEAPON_M249] = kMachinegun;
}



void weapon::InitFOVTable()
{
	kFOVTable[kNonWeapon] = 1000.0f;
	kFOVTable[kPistol] = 2.0f;
	kFOVTable[kShotgun] = 2.0f;
	kFOVTable[kSMG] = 1.7f;
	kFOVTable[kAssaultRifle] = 1.6f;
	kFOVTable[kSniperRifle] = 2.0f;
	kFOVTable[kMachinegun] = 1.5f;
}

void weapon::InitSmoothTable()
{
	kSmoothTable[kNonWeapon] = 170.0f;
	kSmoothTable[kPistol] = 1.8f;
	kSmoothTable[kShotgun] = 4.0f;
	kSmoothTable[kSMG] = 3.8f;
	kSmoothTable[kAssaultRifle] = 3.5f;
	kSmoothTable[kSniperRifle] = 1.0f;
	kSmoothTable[kMachinegun] = 3.8f;
}