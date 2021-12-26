#include "game.h"


DWORD game::client_state = NULL;
DWORD game::net_channel = NULL;
int game::connection_state = 0;
GlobalVar game::server_info;
int game::tick_rate = 0;
int game::local_player_index = 0;
EntityAddress game::player_entity_address_list[client::kMaxPlayerNum] = {};


Entity game::player_entity_list[client::kMaxPlayerNum] = {};
bool game::player_entity_is_valid[client::kMaxPlayerNum] = {};
bool game::player_entity_is_visible[client::kMaxPlayerNum] = {};


BoneMatrix game::bone_matrix_list[client::kMaxPlayerNum][BoneMatrix::kMaxBoneNum] = {};


int game::curr_weapon_entity_index = 0;
DWORD game::curr_weapon_entity_address = NULL;
short game::curr_weapon_def_index = 0;




byte game::fakelag_hotkey = VK_F6;
byte game::remove_flash_hotkey = VK_F7;
byte game::bhop_hotkey = VK_F8;
byte game::glow_esp_hotkey = VK_F9;
byte game::radar_esp_hotkey = VK_F10;
byte game::thirdperson_hotkey = VK_OEM_MINUS;
byte game::desync_hotkey = VK_OEM_PLUS;
byte game::aimbot_fire_hotkey = VK_OEM_4;
byte game::aimbot_backtrack_hotkey = VK_OEM_6;
byte game::global_target_hotkey = VK_OEM_5;
byte game::rcs_hotkey = 0;

short game::toggle_mode[255] = {};