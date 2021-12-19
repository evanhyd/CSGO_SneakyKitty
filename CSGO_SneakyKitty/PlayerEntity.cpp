#include "PlayerEntity.h"


/*

DWORD PlayerEntity::local_player = NULL;
int PlayerEntity::local_player_index = 0;
int PlayerEntity::local_player_team = PlayerEntity::Team::INVALID;
PlayerEntity PlayerEntity::player_entity_list[client::MAX_PLAYER];

bool PlayerEntity::IsValidPlayerEntity(int entity_index)
{
	return PlayerEntityAddress::player_entity_address_list[entity_index].entity_address != NULL &&
		!player_entity_list[entity_index].dormant && player_entity_list[entity_index].health > 0 &&
		(player_entity_list[entity_index].team == PlayerEntity::Team::T || player_entity_list[entity_index].team == PlayerEntity::Team::CT);
}


bool PlayerEntity::IsVisibleToSpectator(int being_spectated_index, int spectator_index)
{
	return hotkey::key_binds[hotkey::RAGEBOT].second || hotkey::key_binds[hotkey::BATTLEROYALE].second ||
		player_entity_list[being_spectated_index].spotted_by_mask & 1 << spectator_index;
}


void PlayerEntity::PlayerEntityUpdate()
{
	while (true)
	{
		if (client::connection_status != client::ConnectionState::FULLY_CONNECTED)
		{
			Sleep(3000);
			continue;
		}

		ReadProcessMemory(module::csgo_handle, reinterpret_cast<LPCVOID>(module::client_dll + dwEntityList), PlayerEntityAddress::player_entity_address_list, sizeof(PlayerEntityAddress::player_entity_address_list), NULL);

		rM(client::client_state + dwClientState_GetLocalPlayer, PlayerEntity::local_player_index);

		//read the entities' information
		for (int entity_index = 0; entity_index < client::MAX_PLAYER; ++entity_index)
		{
			if (PlayerEntityAddress::player_entity_address_list[entity_index].entity_address == NULL) continue;

			//read the entity's information
			rM(PlayerEntityAddress::player_entity_address_list[entity_index].entity_address + player_entity_entry, PlayerEntity::player_entity_list[entity_index]);
		}

		PlayerEntity::local_player_team = PlayerEntity::player_entity_list[PlayerEntity::local_player_index].team;

		for (int entity_index = 0; entity_index < client::MAX_PLAYER; ++entity_index)
		{
			if (entity_index == PlayerEntity::local_player_index) continue;

			//check the entity status
			if (PlayerEntity::IsValidPlayerEntity(entity_index))
			{
				if (hotkey::key_binds[hotkey::BATTLEROYALE].second || PlayerEntity::player_entity_list[entity_index].team != PlayerEntity::local_player_team)
				{
					PlayerEntity::player_entity_list[entity_index].team = PlayerEntity::Team::ENEMY;
				}
				else
				{
					PlayerEntity::player_entity_list[entity_index].team = PlayerEntity::Team::ALLY;
				}
			}
			else PlayerEntity::player_entity_list[entity_index].team = PlayerEntity::Team::INVALID;
		}

		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

*/