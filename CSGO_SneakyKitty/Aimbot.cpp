#include "Aimbot.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "Angle.h"
#include "Position.h"
#include "weapon.h"
#include "Backtrack.h"
#include "BacktrackRecord.h"
#include "user_interface.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <deque>
#include <map>

using namespace user_interface;

bool Aimbot::QualifyAimbotRule(int bone_id)
{
    //always check teaser fisrt, because it should NEVER aim for neck or head
    return !(game::curr_weapon_def_index == weapon::WEAPON_TASER && (bone_id == BoneMatrix::kNeck || bone_id == BoneMatrix::kHead));
}

void Aimbot::operator()(int update_period_ms)
{
    //target pos - local player pos
    Position target{}, relative{};

    //bullet = crosshair_angle + recoil_factor * recoil_angle
    Angle crosshair{}, recoil{}, bullet{};

    //diff = exact - bullet
    Angle exact{}, diff{}, smallest_diff{};

    std::deque<BacktrackRecord> history[client::kMaxPlayerNum][BoneMatrix::kMaxBoneNum]{};

    int curr_tick = 0, backtrack_tick = 0;
    std::thread backtrack_thd(Backtrack(), 1, std::ref(curr_tick), std::ref(backtrack_tick));
    backtrack_thd.detach();

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kAimbot] == 0)
        {
            //clear the history
            for (int entity_id = 0; entity_id < client::kMaxPlayerNum; entity_id++)
            {
                for (int indexed_bone_id = 0; indexed_bone_id < BoneMatrix::kMaxBoneNum; indexed_bone_id++)
                {
                    history[entity_id][indexed_bone_id].clear();
                }
            }
            
            //std::for_each_n(history, client::kMaxPlayerNum * BoneMatrix::kMaxBoneNum, [](auto &records) { records->clear(); });
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        //checking holding a gun
        if (!weapon::IsGun(game::curr_weapon_def_index))
        {
            backtrack_tick = 0;
            continue;
        }

        //set up fov range
        float fov_limit = (toggle_mode[kAimbot] == 1 ? weapon::GetFOV(game::curr_weapon_def_index) : weapon::kRagebotFOV);

        //read the crosshair angle
        memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair);

        //predict the bullet angle, apply recoil if viable
        bullet = crosshair;
        const int weapon_type = weapon::GetWeaponType(game::curr_weapon_def_index);
        if (weapon_type == weapon::kAssaultRifle || weapon_type == weapon::kSMG || weapon_type == weapon::kMachinegun)
        {
            memory::ReadMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_aimPunchAngle, recoil);
            bullet += recoil * weapon::kRecoilFactor;
        }

        //calculate the maximum backtrack tick
        const int max_backtrack_tick = static_cast<int>(client::kMaxLagCompensation / game::server_info.interval_per_tick_) - 1;

#ifdef _DEBUG
        std::clog << "max backtrack tick on the curr server: " << max_backtrack_tick << '\n';
#endif

        //add target position to the aimbot candidate list
        for (int entity_id = 0; entity_id < client::kMaxPlayerNum; ++entity_id)
        {
            //filter out invalid entity 
            if (!game::player_is_valid[entity_id]) continue;

            //filter out ally
            if (game::player_list[game::local_player_index].IsAlly(game::player_list[entity_id]))
            {
                //check global targe mode
                if (user_interface::toggle_mode[kGlobalTarget] == 0) continue;

                //filter out local player
                if (entity_id == game::local_player_index) continue;
            }

            //filter invisible enemy
            else if (toggle_mode[kAimbot] == 1 && !Entity::SpottedBy(entity_id, game::local_player_index)) continue;


            for (int bone_id = BoneMatrix::kBoneBegin; bone_id <= BoneMatrix::kBoneEnd; ++bone_id)
            {
                //check weapon aiming type
                if (!this->QualifyAimbotRule(bone_id)) continue;

                //calculate the relative enemy position with local playe as origin
                target = Position(game::bone_matrix_list[entity_id][bone_id]);

                //convert the bone index
                const int indexed_bone_id = bone_id - BoneMatrix::kBoneBegin;
                
                //push new backtrack if the history is empty or has a new backtrack tick
                if (history[entity_id][indexed_bone_id].empty() ||
                    history[entity_id][indexed_bone_id].front().tick != curr_tick)
                {
                    history[entity_id][indexed_bone_id].emplace_front(curr_tick, target);
                }
                else
                {
                    //update the position to avoid duplicated record
                    history[entity_id][indexed_bone_id].front().pos = target;
                }
            }
        }


        
        


        //reset the target flag, reset chosen backtrack tick
        bool has_target = false;
        int curr_backtrack_tick = 0;
        const int record_to_search = (toggle_mode[kBacktrack] == 1 ? max_backtrack_tick : 1);

        for (int entity_id = 0; entity_id < client::kMaxPlayerNum; ++entity_id)
        {
            //remove invalid entity
            if (!game::player_is_valid[entity_id])
            {
                for (int bone_id = BoneMatrix::kBoneBegin; bone_id <= BoneMatrix::kBoneEnd; ++bone_id)
                {
                    history[entity_id][bone_id].clear();
                }
                continue;
            }

            
            for (int indexed_bone_id = 0; indexed_bone_id < BoneMatrix::kMaxBoneNum; ++indexed_bone_id)
            {
                //remove expired tick
                for(int record_id = history[entity_id][indexed_bone_id].size() - 1; record_id >= 0; --record_id)
                {
                    if (history[entity_id][indexed_bone_id][record_id].tick + max_backtrack_tick < curr_tick) history[entity_id][indexed_bone_id].pop_back();
                    else break;
                }

                
                const int bone_id = indexed_bone_id + BoneMatrix::kBoneBegin;
                int record_searched = 0;
                
                for (const auto& [tick, pos] : history[entity_id][indexed_bone_id])
                {
                    //find the relative distance from the bone to local player eye
                    relative = pos - game::player_list[game::local_player_index].GetOrigin();
                    relative.z_ -= game::player_list[game::local_player_index].GetViewOffsetZ();

                    //calculate aimbot angle, find the angle difference
                    exact.PointTo(relative);
                    diff = exact - bullet;
                    diff.Clamp();

                    //calculate the multipoint radius based on bone radius and distance
                    const float dist_to_enemy = relative.MagnitudeToOrigin();
                    const float multipoint_radius = Angle::ToDegrees(atan2f(BoneMatrix::kBoneRadius[bone_id], dist_to_enemy));

                    //select the closest multipoint angle
                    float increased_yaw = diff.y_ + multipoint_radius;
                    if (increased_yaw > 180.0f) increased_yaw -= 360.0f;
                    float decreased_yaw = diff.y_ - multipoint_radius;
                    if (decreased_yaw < -180.0f) decreased_yaw += 360.0f;

                    const float abs_difference_yaw = abs(diff.y_);
                    const float abs_increased_yaw = abs(increased_yaw);
                    const float abs_decreased_yaw = abs(decreased_yaw);

                    if (abs_increased_yaw < abs_difference_yaw && abs_increased_yaw < abs_decreased_yaw) diff.y_ = increased_yaw;
                    else if (abs_decreased_yaw < abs_difference_yaw && abs_decreased_yaw < abs_increased_yaw) diff.y_ = decreased_yaw;


                    //choose the smallest one
                    const float curr_fov = diff.FOVMagnitude();
                    if (curr_fov < fov_limit)
                    {
                        smallest_diff = diff;
                        fov_limit = curr_fov;

                        has_target = true;
                        curr_backtrack_tick = tick;
                    }
                    
                    //check searched record, no more than once without backtrack
                    if (++record_searched == record_to_search) break;
                }
            }
        }
        
        
        backtrack_tick = curr_backtrack_tick;

        //check if selected a target
        if (!has_target) continue;

        //legit aimbot smooth aim step
        if (toggle_mode[kAimbot] == 1) smallest_diff /= weapon::GetSmooth(game::curr_weapon_def_index);

        //apply the angle modification
        crosshair += smallest_diff;
        crosshair.Clamp();

        //left click mouse to fire
        if (GetAsyncKeyState(0x01) & (1 << 15)) memory::WriteMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair);

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}