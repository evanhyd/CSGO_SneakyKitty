#pragma once

namespace weapon
{
	enum DefinitionIndex : short
	{
		WEAPON_INVALID = -1,

		//pistol
		WEAPON_DEAGLE = 1,
		WEAPON_ELITE,
		WEAPON_FIVESEVEN,
		WEAPON_GLOCK,


		//assault rifle
		WEAPON_AK47 = 7,
		WEAPON_AUG,

		//sniper rifle
		WEAPON_AWP,

		WEAPON_FAMAS,
		WEAPON_G3SG1,
		WEAPON_GALILAR = 13,
		WEAPON_M249,
		WEAPON_M4A1 = 16,
		WEAPON_MAC10,
		WEAPON_P90 = 19,
		WEAPON_MP5 = 23,
		WEAPON_UMP45,
		WEAPON_XM1014,
		WEAPON_BIZON,
		WEAPON_MAG7,
		WEAPON_NEGEV,
		WEAPON_SAWEDOFF,

		//pistol
		WEAPON_TEC9,
		WEAPON_TASER,
		WEAPON_HKP2000,

		WEAPON_MP7,
		WEAPON_MP9,
		WEAPON_NOVA,

		//pistol
		WEAPON_P250,

		WEAPON_SHIELD,
		WEAPON_SCAR20,
		WEAPON_SG556,
		WEAPON_SSG08,


		WEAPON_KNIFEGG,
		WEAPON_KNIFE,

		//grenades
		WEAPON_FLASHBANG,
		WEAPON_HEGRENADE,
		WEAPON_SMOKEGRENADE,
		WEAPON_MOLOTOV,
		WEAPON_DECOY,
		WEAPON_INCGRENADE,

		//c4
		WEAPON_C4,

		//others
		WEAPON_HEALTHSHOT = 57,
		WEAPON_KNIFE_T = 59,

		WEAPON_M4A1_SILENCER,
		WEAPON_USP_SILENCER,
		WEAPON_CZ75A = 63,
		WEAPON_REVOLVER
	};

	enum ConfigType : int
	{
		kNonWeapon,
		kPistol,
		kShotgun,
		kSMG,
		kAssaultRifle,
		kMachinegun,
		kSniperRifle
	};



	constexpr float kRecoilFactor = 2.0f;
	constexpr float kRagebotFOV = 180.0f;
	constexpr int kWeaponNum = 65;
	constexpr int kConfigNum = 7;


	extern bool kIsGunTable[kWeaponNum];
	extern int kConfigTypeTable[kWeaponNum];
	extern float kFOVTable[kConfigNum];
	extern float kSmoothTable[kConfigNum];


	void InitIsGunTable();
	void InitConfigTypeTable();
	void InitFOVTable();
	void InitSmoothTable();


	/*void WeaponUpdate();*/
	/*extern int current_weapon_entity_index;
	extern DWORD current_weapon_entity_address;
	extern short current_weapon_def_index;*/
}
