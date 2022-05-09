#include "game.h"


DWORD game::client_state = NULL;
DWORD game::net_channel = NULL;
int game::connection_state = 0;
GlobalVar game::server_info;
int game::tick_rate = 0;
int game::local_player_index = 0;
EntityAddress game::player_address_list[client::kMaxPlayerNum] = {};


Entity game::player_list[client::kMaxPlayerNum] = {};
bool game::player_is_valid[client::kMaxPlayerNum] = {};
bool game::player_is_visible[client::kMaxPlayerNum] = {};


BoneMatrix game::bone_matrix_list[client::kMaxPlayerNum][BoneMatrix::kMaxBoneNum] = {};


int game::curr_weapon_entity_index = 0;
DWORD game::curr_weapon_entity_address = NULL;
short game::curr_weapon_def_index = 0;




InputCmd game::input_cmd = {};
int game::last_outgoing_cmd_num = 0;
DWORD game::curr_cmd_address = NULL;
DWORD game::curr_verified_cmd_address = NULL;