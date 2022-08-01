#include "Fakelag.h"

#include "BoneMatrix.h"


void Fakelag::ChokePackets(int max_choke_ticks)
{
	memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, false);

	int curr_choked_ticks = 999;
	do
	{
		memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::clientstate_choked_commands, curr_choked_ticks);
	} while (curr_choked_ticks < max_choke_ticks);

	memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);
}


bool Fakelag::OnExecute()
{
	const int max_choke_tick = static_cast<int>(game::kMaxLagCompensation / game::server_info.interval_per_tick_) - 2;

	//anti-trigger
	switch (user_interface::toggle_mode[user_interface::kFakelag])
	{
	case 1:
		for (int entity_id = 0; entity_id < game::kMaxPlayerNum; ++entity_id)
		{
			//filter out invalid entity
			if (!game::player_is_valid[entity_id]) continue;

			//check global target mode and team
			if (user_interface::toggle_mode[user_interface::kGlobalTarget] == 0 && game::player_list[game::local_player_index].IsAlly(game::player_list[entity_id])) continue;


			//calculate the aimbot angle for the enemy
			relative_pos_ = Position(game::bone_matrix_list[game::local_player_index][BoneMatrix::kChest]) - Position(game::bone_matrix_list[entity_id][BoneMatrix::kHead]);
			enemy_aimbot_angle_.PointTo(relative_pos_);


			//get the enemy's actual angle
			memory::ReadMem(module::csgo_proc_handle, game::player_address_list[entity_id].GetAddress() + offsets::m_angEyeAnglesX, enemy_eye_angle_);


			//convert third person angle to first person angle
			// pitch: [0.0f, 89.0f] U [271.0f, 360.0f]
			// yaw: [0.0f : 360.0f]
			if (enemy_eye_angle_.x_ >= 271.0f) enemy_eye_angle_.x_ -= 360.0f;
			if (enemy_eye_angle_.y_ > 180.0f) enemy_eye_angle_.y_ -= 360.0f;


			//calculate the differences
			enemy_difference_angle_ = enemy_eye_angle_ - enemy_aimbot_angle_;
			enemy_difference_angle_.Clamp();


			//calculate the dangerzone angle range
			const float danger_difference_angle = Angle::ToDegrees(atan2f(BoneMatrix::kPlayerRadius, relative_pos_.MagnitudeToOrigin()));


			//if the enemy crosshair is too close to the player
			if (enemy_difference_angle_.FOVMagnitude() < danger_difference_angle) this->ChokePackets(max_choke_tick);

		}
		break;


		//V for fakelag
	case 2:
		if (GetAsyncKeyState('C') & 1 << 15) ChokePackets(max_choke_tick);
		break;


		//always fakelag
	case 3:
		ChokePackets(max_choke_tick);
		break;
	}

	return false;
}