#include "Aimbot.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "Angle.h"
#include "Position.h"
#include "weapon.h"
#include "Backtrack.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <deque>

bool Aimbot::QualifyAimbotRule(int bone_i)
{
    //always check teaser fisrt, because it should NEVER aim for neck or head
    if (game::curr_weapon_def_index == weapon::WEAPON_TASER && (bone_i == BoneMatrix::kNeck || bone_i == BoneMatrix::kHead)) return false;

    //aimbot mode 2 only aim for head or neck
    if (game::toggle_mode[game::aimbot_fire_hotkey] == 2 && bone_i != BoneMatrix::kNeck && bone_i != BoneMatrix::kHead) return false;

    //aimbot mode 3 aim for all bones
    return true;
}

void Aimbot::operator()(int update_period_ms)
{
    //enemy pos - local player pos
    Position relative;

    //bullet = crosshair_angle + recoil_factor * recoil_angle
    Angle crosshair;
    Angle recoil;
    Angle bullet;

    //difference = exact - bullet
    Angle exact;
    Angle difference;
    Angle closest;

    //tick, angle
    std::deque<std::pair<int, Angle>> backtrack_angles;
    bool has_cleared_backtrack_history = true;

    int curr_tick = 0;
    int backtrack_tick = 0;
    std::thread backtrack_thd(Backtrack(), 1, std::ref(curr_tick), std::ref(backtrack_tick));
    backtrack_thd.detach();
    

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || game::toggle_mode[game::aimbot_fire_hotkey] == 0)
        {
            if (!has_cleared_backtrack_history)
            {
                backtrack_angles.clear();
                has_cleared_backtrack_history = true;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        has_cleared_backtrack_history = false;

        if (weapon::IsGun(game::curr_weapon_def_index))
        {
            float closest_fov = 181.0f;

            //obtain the fov setting
            float fov_limit = (game::toggle_mode[game::aimbot_fire_hotkey] == 1 ? weapon::GetFOV(game::curr_weapon_def_index) : weapon::kRagebotFOV);


            //read the crosshair angle
            memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair);
            bullet = crosshair;


            //apply recoil if viable
            int weapon_type = weapon::GetWeaponType(game::curr_weapon_def_index);
            if (weapon_type == weapon::kAssaultRifle || weapon_type == weapon::kSMG || weapon_type == weapon::kMachinegun)
            {
                memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[game::local_player_index].GetAddress() + offsets::m_aimPunchAngle, recoil);
                bullet += recoil * weapon::kRecoilFactor;
            }


            //calculate the maximum backtrack tick
            int max_backtrack_tick = static_cast<int>(client::kMaxLagCompensation / game::server_info.interval_per_tick_);
            backtrack_tick = -1;


            //aimbot 
            for (int entity_i = 0; entity_i < client::kMaxPlayerNum; ++entity_i)
            {
                //filter out invalid entity 
                if (!game::player_entity_is_valid[entity_i]) continue;

                //filter out local player
                if (entity_i == game::local_player_index) continue;

                //check global targe mode
                if (game::toggle_mode[game::global_target_hotkey] == 0)
                {
                    //filter out ally
                    if (game::player_entity_list[game::local_player_index].IsAlly(game::player_entity_list[entity_i])) continue;

                    //check visibility and rage setting
                    if ((game::player_entity_list[entity_i].GetSpottedMask() >> game::local_player_index & 1) == 0) continue;
                }


                for (int bone_i = BoneMatrix::kBoneBegin; bone_i <= BoneMatrix::kBoneEnd; ++bone_i)
                {
                    if (!this->QualifyAimbotRule(bone_i)) continue;

                    //calculate the relative enemy position with local playe as origin
                    relative = Position(game::bone_matrix_list[entity_i][bone_i]) - game::player_entity_list[game::local_player_index].GetOrigin();


                    //bullets shoot from player's eyes, subtract the relative height
                    relative.z_ -= game::player_entity_list[game::local_player_index].GetViewOffsetZ();


                    //calculate the exact aimbot angle
                    exact.PointTo(relative);


                    //add to the backtrack candidates
                    if (game::toggle_mode[game::aimbot_backtrack_hotkey] == 1) backtrack_angles.push_back({ curr_tick, exact });


                    //calculate the difference between the exact and the bullet
                    difference = exact - bullet;
                    difference.Clamp();

                    //calculate multipoint radius
                    float dist_to_enemy = relative.MagnitudeToOrigin();
                    float multipoint_radius = Angle::ToDegrees(atan2f(BoneMatrix::kBoneRadius[bone_i], dist_to_enemy));


                    //calculate the multipoint based on the radius
                    //here only applies horizontal multipoint 
                    float increased_yaw = difference.y_ + multipoint_radius;
                    if (increased_yaw > 180.0f) increased_yaw -= 360.0f;

                    float decreased_yaw = difference.y_ - multipoint_radius;
                    if (decreased_yaw < -180.0f) decreased_yaw += 360.0f;

                    if (abs(increased_yaw) < abs(difference.y_) && abs(increased_yaw) < abs(decreased_yaw)) difference.y_ = increased_yaw;
                    else if(abs(decreased_yaw) < abs(difference.y_) && abs(decreased_yaw) < abs(increased_yaw)) difference.y_ = decreased_yaw;


                    float curr_fov = difference.FOVMagnitude();
                    if (curr_fov < fov_limit && curr_fov < closest_fov)
                    {
                        closest = difference;
                        closest_fov = curr_fov;
                    }
                }
            }


            if (game::toggle_mode[game::aimbot_backtrack_hotkey] == 1)
            {
                while (!backtrack_angles.empty())
                {
                    if (curr_tick - backtrack_angles.front().first > max_backtrack_tick) backtrack_angles.pop_front();
                    else break;
                }

                for (const auto& backtrack_candidate : backtrack_angles)
                {
                    difference = backtrack_candidate.second - bullet;
                    difference.Clamp();

                    //calculate the fov
                    float curr_fov = difference.FOVMagnitude();

                    //choose the smallest one
                    if (curr_fov < fov_limit && curr_fov < closest_fov)
                    {
                        closest = difference;
                        closest_fov = curr_fov;
                        backtrack_tick = backtrack_candidate.first;
                    }
                }
            }

            if (closest_fov == 181.0f) continue;

            //smooth the aimbot
            if (game::toggle_mode[game::aimbot_fire_hotkey] == 1) closest /= weapon::GetSmooth(game::curr_weapon_def_index);

            //apply the angle modification
            crosshair += closest;
            crosshair.Clamp();

            if (GetAsyncKeyState(0x01) & 1 << 15) memory::WriteMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}
