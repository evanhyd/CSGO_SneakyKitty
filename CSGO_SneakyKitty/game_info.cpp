#include "game_info.h"


DWORD game_info::client_state = NULL;
DWORD game_info::net_channel = NULL;
int game_info::connection_state = 0;

GlobalVar game_info::server_info;
int game_info::tick_rate = 0;

int game_info::local_player_index = 0;
PlayerEntityAddress game_info::player_entity_address_list[client::kMaxPlayerNum] = {};
