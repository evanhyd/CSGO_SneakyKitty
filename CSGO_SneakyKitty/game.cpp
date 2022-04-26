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




InputCmd game::input_cmd = {};
int game::last_outgoing_cmd_num = 0;
DWORD game::curr_cmd_address = NULL;
DWORD game::curr_verified_cmd_address = NULL;



uint8_t game::fakelag_hotkey = VK_F6;
uint8_t game::remove_flash_hotkey = VK_F7;
uint8_t game::bhop_hotkey = VK_F8;
uint8_t game::glow_esp_hotkey = VK_F9;
uint8_t game::radar_esp_hotkey = VK_F10;
uint8_t game::thirdperson_hotkey = VK_OEM_MINUS;
uint8_t game::desync_hotkey = VK_OEM_PLUS;
uint8_t game::aimbot_fire_hotkey = VK_OEM_4;
uint8_t game::aimbot_backtrack_hotkey = VK_OEM_6;
uint8_t game::global_target_hotkey = VK_OEM_5;
uint8_t game::rcs_hotkey = 0;

short game::toggle_mode[255] = {};