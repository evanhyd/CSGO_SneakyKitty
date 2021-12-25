#include "Fakelag.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "Angle.h"
#include "Position.h"
#include "BoneMatrix.h"

#include <iostream>
#include <thread>
#include <chrono>


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


void Fakelag::operator()(int update_period_ms)
{
    Angle enemy_eye_angle;
    Angle enemy_aimbot_angle;
    Angle enemy_difference_angle;
    Position relative_pos;


    while (true)
    {
        if (game::connection_state != client::kFullyConnected || game::toggle_mode[game::fakelag_hotkey] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

		int max_choke_tick = static_cast<int>(client::kMaxLagCompensation / game::server_info.interval_per_tick_) - 1;


		//anti-trigger
		switch (game::toggle_mode[game::fakelag_hotkey])
		{
		case 1:
			for (int i = 0; i < client::kMaxPlayerNum; ++i)
			{
				if (!game::player_entity_is_valid[i]) continue;
				if (!game::toggle_mode[game::global_target_hotkey] && game::player_entity_list[game::local_player_index].IsAlly(game::player_entity_list[i])) continue;


				//calculate the aimbot angle for the enemy
				relative_pos = Position(game::bone_matrix_list[game::local_player_index][BoneMatrix::kChest]) - Position(game::bone_matrix_list[i][BoneMatrix::kHead]);
				enemy_aimbot_angle.PointTo(relative_pos);


				//get the enemy's actual angle
				memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[i].GetAddress() + offsets::m_angEyeAnglesX, enemy_eye_angle);


				//convert third person angle to first person angle
				// pitch: [0.0f, 89.0f] U [271.0f, 360.0f]
				// yaw: [0.0f : 360.0f]
				if (enemy_eye_angle.x_ >= 271.0f) enemy_eye_angle.x_ -= 360.0f;
				if (enemy_eye_angle.y_ > 180.0f) enemy_eye_angle.y_ -= 360.0f;


				//calculate the differences
				enemy_difference_angle = enemy_eye_angle - enemy_aimbot_angle;
				enemy_difference_angle.Clamp();


				//calculate the dangerzone angle range
				float danger_difference_angle = Angle::ToDegrees(atan2f(BoneMatrix::kPlayerRadius, relative_pos.MagnitudeToOrigin()));


				//if the enemy crosshair is too close to the player
				if (enemy_difference_angle.MagnitudeToCrosshair() < danger_difference_angle) this->ChokePackets(max_choke_tick);

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

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}