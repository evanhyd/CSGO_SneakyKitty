#include "client.h"

//int client::connection_status = client::ConnectionState::kNone;


//void client::UpdateClient()
//{
//
//}


/*

#include "client.h"
#include "PlayerEntityAddress.h"
#include "PlayerEntity.h"

DWORD client::client_state = NULL;
DWORD client::net_channel = NULL;
int client::connection_status = NULL;


void client::ClientUpdate()
{
	rM(module::client_dll + dwLocalPlayer, PlayerEntity::local_player);
	rM(module::engine_dll + dwClientState, client_state);
	rM(client::client_state + clientstate_net_channel, net_channel);
	rM(client_state + dwClientState_State, connection_status);

	//read 32 players' address together
	ReadProcessMemory(module::csgo_handle, reinterpret_cast<LPCVOID>(module::client_dll + dwEntityList), PlayerEntityAddress::player_entity_address_list, sizeof(PlayerEntityAddress::player_entity_address_list), NULL);

	this_thread::sleep_for(chrono::milliseconds(5000));
}


*/