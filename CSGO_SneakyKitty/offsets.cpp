#include "offsets.h"
#include "Input.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>


DWORD offsets::cs_gamerules_data = 0;
DWORD offsets::m_ArmorValue = 0;
DWORD offsets::m_Collision = 0;
DWORD offsets::m_CollisionGroup = 0;
DWORD offsets::m_Local = 0;
DWORD offsets::m_MoveType = 0;
DWORD offsets::m_OriginalOwnerXuidHigh = 0;
DWORD offsets::m_OriginalOwnerXuidLow = 0;
DWORD offsets::m_SurvivalGameRuleDecisionTypes = 0;
DWORD offsets::m_SurvivalRules = 0;
DWORD offsets::m_aimPunchAngle = 0;
DWORD offsets::m_aimPunchAngleVel = 0;
DWORD offsets::m_angEyeAnglesX = 0;
DWORD offsets::m_angEyeAnglesY = 0;
DWORD offsets::m_bBombDefused = 0;
DWORD offsets::m_bBombPlanted = 0;
DWORD offsets::m_bBombTicking = 0;
DWORD offsets::m_bFreezePeriod = 0;
DWORD offsets::m_bGunGameImmunity = 0;
DWORD offsets::m_bHasDefuser = 0;
DWORD offsets::m_bHasHelmet = 0;
DWORD offsets::m_bInReload = 0;
DWORD offsets::m_bIsDefusing = 0;
DWORD offsets::m_bIsQueuedMatchmaking = 0;
DWORD offsets::m_bIsScoped = 0;
DWORD offsets::m_bIsValveDS = 0;
DWORD offsets::m_bSpotted = 0;
DWORD offsets::m_bSpottedByMask = 0;
DWORD offsets::m_bStartedArming = 0;
DWORD offsets::m_bUseCustomAutoExposureMax = 0;
DWORD offsets::m_bUseCustomAutoExposureMin = 0;
DWORD offsets::m_bUseCustomBloomScale = 0;
DWORD offsets::m_clrRender = 0;
DWORD offsets::m_dwBoneMatrix = 0;
DWORD offsets::m_fAccuracyPenalty = 0;
DWORD offsets::m_fFlags = 0;
DWORD offsets::m_flC4Blow = 0;
DWORD offsets::m_flCustomAutoExposureMax = 0;
DWORD offsets::m_flCustomAutoExposureMin = 0;
DWORD offsets::m_flCustomBloomScale = 0;
DWORD offsets::m_flDefuseCountDown = 0;
DWORD offsets::m_flDefuseLength = 0;
DWORD offsets::m_flFallbackWear = 0;
DWORD offsets::m_flFlashDuration = 0;
DWORD offsets::m_flFlashMaxAlpha = 0;
DWORD offsets::m_flLastBoneSetupTime = 0;
DWORD offsets::m_flLowerBodyYawTarget = 0;
DWORD offsets::m_flNextAttack = 0;
DWORD offsets::m_flNextPrimaryAttack = 0;
DWORD offsets::m_flSimulationTime = 0;
DWORD offsets::m_flTimerLength = 0;
DWORD offsets::m_hActiveWeapon = 0;
DWORD offsets::m_hBombDefuser = 0;
DWORD offsets::m_hMyWeapons = 0;
DWORD offsets::m_hObserverTarget = 0;
DWORD offsets::m_hOwner = 0;
DWORD offsets::m_hOwnerEntity = 0;
DWORD offsets::m_hViewModel = 0;
DWORD offsets::m_iAccountID = 0;
DWORD offsets::m_iClip1 = 0;
DWORD offsets::m_iCompetitiveRanking = 0;
DWORD offsets::m_iCompetitiveWins = 0;
DWORD offsets::m_iCrosshairId = 0;
DWORD offsets::m_iDefaultFOV = 0;
DWORD offsets::m_iEntityQuality = 0;
DWORD offsets::m_iFOV = 0;
DWORD offsets::m_iFOVStart = 0;
DWORD offsets::m_iGlowIndex = 0;
DWORD offsets::m_iHealth = 0;
DWORD offsets::m_iItemDefinitionIndex = 0;
DWORD offsets::m_iItemIDHigh = 0;
DWORD offsets::m_iMostRecentModelBoneCounter = 0;
DWORD offsets::m_iObserverMode = 0;
DWORD offsets::m_iShotsFired = 0;
DWORD offsets::m_iState = 0;
DWORD offsets::m_iTeamNum = 0;
DWORD offsets::m_lifeState = 0;
DWORD offsets::m_nBombSite = 0;
DWORD offsets::m_nFallbackPaintKit = 0;
DWORD offsets::m_nFallbackSeed = 0;
DWORD offsets::m_nFallbackStatTrak = 0;
DWORD offsets::m_nForceBone = 0;
DWORD offsets::m_nTickBase = 0;
DWORD offsets::m_nViewModelIndex = 0;
DWORD offsets::m_rgflCoordinateFrame = 0;
DWORD offsets::m_szCustomName = 0;
DWORD offsets::m_szLastPlaceName = 0;
DWORD offsets::m_thirdPersonViewAngles = 0;
DWORD offsets::m_vecOrigin = 0;
DWORD offsets::m_vecVelocity = 0;
DWORD offsets::m_vecViewOffset = 0;
DWORD offsets::m_viewPunchAngle = 0;
DWORD offsets::m_zoomLevel = 0;
DWORD offsets::anim_overlays = 0;
DWORD offsets::clientstate_choked_commands = 0;
DWORD offsets::clientstate_delta_ticks = 0;
DWORD offsets::clientstate_last_outgoing_command = 0;
DWORD offsets::clientstate_net_channel = 0;
DWORD offsets::convar_name_hash_table = 0;
DWORD offsets::dwClientState = 0;
DWORD offsets::dwClientState_GetLocalPlayer = 0;
DWORD offsets::dwClientState_IsHLTV = 0;
DWORD offsets::dwClientState_Map = 0;
DWORD offsets::dwClientState_MapDirectory = 0;
DWORD offsets::dwClientState_MaxPlayer = 0;
DWORD offsets::dwClientState_PlayerInfo = 0;
DWORD offsets::dwClientState_State = 0;
DWORD offsets::dwClientState_ViewAngles = 0;
DWORD offsets::dwEntityList = 0;
DWORD offsets::dwForceAttack = 0;
DWORD offsets::dwForceAttack2 = 0;
DWORD offsets::dwForceBackward = 0;
DWORD offsets::dwForceForward = 0;
DWORD offsets::dwForceJump = 0;
DWORD offsets::dwForceLeft = 0;
DWORD offsets::dwForceRight = 0;
DWORD offsets::dwGameDir = 0;
DWORD offsets::dwGameRulesProxy = 0;
DWORD offsets::dwGetAllClasses = 0;
DWORD offsets::dwGlobalVars = 0;
DWORD offsets::dwGlowObjectManager = 0;
DWORD offsets::dwInput = 0;
DWORD offsets::dwInterfaceLinkList = 0;
DWORD offsets::dwLocalPlayer = 0;
DWORD offsets::dwMouseEnable = 0;
DWORD offsets::dwMouseEnablePtr = 0;
DWORD offsets::dwPlayerResource = 0;
DWORD offsets::dwRadarBase = 0;
DWORD offsets::dwSensitivity = 0;
DWORD offsets::dwSensitivityPtr = 0;
DWORD offsets::dwSetClanTag = 0;
DWORD offsets::dwViewMatrix = 0;
DWORD offsets::dwWeaponTable = 0;
DWORD offsets::dwWeaponTableIndex = 0;
DWORD offsets::dwYawPtr = 0;
DWORD offsets::dwZoomSensitivityRatioPtr = 0;
DWORD offsets::dwbSendPackets = 0;
DWORD offsets::dwppDirect3DDevice9 = 0;
DWORD offsets::find_hud_element = 0;
DWORD offsets::force_update_spectator_glow = 0;
DWORD offsets::interface_engine_cvar = 0;
DWORD offsets::is_c4_owner = 0;
DWORD offsets::m_bDormant = 0;
DWORD offsets::m_flSpawnTime = 0;
DWORD offsets::m_pStudioHdr = 0;
DWORD offsets::m_pitchClassPtr = 0;
DWORD offsets::m_yawClassPtr = 0;
DWORD offsets::model_ambient_min = 0;
DWORD offsets::set_abs_angles = 0;
DWORD offsets::set_abs_origin = 0;
DWORD offsets::player_entity_struct_entry = 0;
DWORD offsets::input_cmd_entry = 0;
DWORD offsets::dwGlowObjectManager_size = 0;


void offsets::UpdateOffsets()
{
	//hazedumper
	//system("curl https://raw.githubusercontent.com/frk1/hazedumper/master/csgo.hpp -o offsets.txt");

	//blazedumper, much faster lol
	system("curl https://raw.githubusercontent.com/Akandesh/blazedumper/master/csgo.hpp -o offsets.txt");
    std::ifstream offsets_file("offsets.txt");


    //parse the file
    //filter out the first 8 lines
    std::string line;
    for (int i = 0; i < 8; ++i)
    {
        std::getline(offsets_file, line);
    }


	std::getline(offsets_file, line);
	offsets::cs_gamerules_data = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_ArmorValue = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_Collision = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_CollisionGroup = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_Local = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_MoveType = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_OriginalOwnerXuidHigh = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_OriginalOwnerXuidLow = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_SurvivalGameRuleDecisionTypes = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_SurvivalRules = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_aimPunchAngle = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_aimPunchAngleVel = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_angEyeAnglesX = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_angEyeAnglesY = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bBombDefused = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bBombPlanted = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bBombTicking = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bFreezePeriod = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bGunGameImmunity = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bHasDefuser = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bHasHelmet = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bInReload = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bIsDefusing = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bIsQueuedMatchmaking = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bIsScoped = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bIsValveDS = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bSpotted = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bSpottedByMask = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bStartedArming = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bUseCustomAutoExposureMax = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bUseCustomAutoExposureMin = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bUseCustomBloomScale = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_clrRender = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_dwBoneMatrix = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_fAccuracyPenalty = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_fFlags = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flC4Blow = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flCustomAutoExposureMax = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flCustomAutoExposureMin = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flCustomBloomScale = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flDefuseCountDown = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flDefuseLength = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flFallbackWear = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flFlashDuration = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flFlashMaxAlpha = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flLastBoneSetupTime = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flLowerBodyYawTarget = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flNextAttack = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flNextPrimaryAttack = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flSimulationTime = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flTimerLength = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_hActiveWeapon = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_hBombDefuser = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_hMyWeapons = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_hObserverTarget = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_hOwner = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_hOwnerEntity = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_hViewModel = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iAccountID = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iClip1 = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iCompetitiveRanking = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iCompetitiveWins = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iCrosshairId = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iDefaultFOV = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iEntityQuality = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iFOV = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iFOVStart = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iGlowIndex = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iHealth = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iItemDefinitionIndex = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iItemIDHigh = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iMostRecentModelBoneCounter = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iObserverMode = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iShotsFired = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iState = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_iTeamNum = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_lifeState = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_nBombSite = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_nFallbackPaintKit = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_nFallbackSeed = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_nFallbackStatTrak = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_nForceBone = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_nTickBase = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_nViewModelIndex = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_rgflCoordinateFrame = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_szCustomName = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_szLastPlaceName = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_thirdPersonViewAngles = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_vecOrigin = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_vecVelocity = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_vecViewOffset = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_viewPunchAngle = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_zoomLevel = ParseOffset(line);


	//filter invalid lines
	std::getline(offsets_file, line);
	std::getline(offsets_file, line);



	std::getline(offsets_file, line);
	offsets::anim_overlays = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::clientstate_choked_commands = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::clientstate_delta_ticks = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::clientstate_last_outgoing_command = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::clientstate_net_channel = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::convar_name_hash_table = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwClientState = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwClientState_GetLocalPlayer = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwClientState_IsHLTV = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwClientState_Map = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwClientState_MapDirectory = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwClientState_MaxPlayer = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwClientState_PlayerInfo = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwClientState_State = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwClientState_ViewAngles = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwEntityList = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwForceAttack = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwForceAttack2 = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwForceBackward = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwForceForward = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwForceJump = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwForceLeft = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwForceRight = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwGameDir = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwGameRulesProxy = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwGetAllClasses = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwGlobalVars = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwGlowObjectManager = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwInput = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwInterfaceLinkList = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwLocalPlayer = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwMouseEnable = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwMouseEnablePtr = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwPlayerResource = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwRadarBase = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwSensitivity = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwSensitivityPtr = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwSetClanTag = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwViewMatrix = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwWeaponTable = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwWeaponTableIndex = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwYawPtr = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwZoomSensitivityRatioPtr = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwbSendPackets = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::dwppDirect3DDevice9 = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::find_hud_element = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::force_update_spectator_glow = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::interface_engine_cvar = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::is_c4_owner = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_bDormant = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_flSpawnTime = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_pStudioHdr = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_pitchClassPtr = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::m_yawClassPtr = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::model_ambient_min = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::set_abs_angles = ParseOffset(line);

	std::getline(offsets_file, line);
	offsets::set_abs_origin = ParseOffset(line);


	//subtract 1 fix padding
	offsets::player_entity_struct_entry = m_bDormant - 1;

	//-8, only looking for the last two commands address
	offsets::input_cmd_entry = offsets::dwInput + sizeof(Input) - 8;


	offsets::dwGlowObjectManager_size = dwGlowObjectManager + 0xc;
}

DWORD offsets::ParseOffset(const std::string& line)
{
    int first = line.rfind(' ');
    int last = line.rfind(';');

    return std::stoi(line.substr(first, last - first), nullptr, 16);
}