#include "Aimbot.h"

#include "weapon.h"
#include "Backtrack.h"
#include <thread>


bool Aimbot::QualifyAimbotRule(int bone_id)
{
    //always check teaser fisrt, because it should NEVER aim for neck or head
    return !(game::curr_weapon_def_index == weapon::WEAPON_TASER && (bone_id == BoneMatrix::kNeck || bone_id == BoneMatrix::kHead));
}


bool Aimbot::OnInitialize()
{
    std::thread backtrack_thd(Backtrack(), 5000, 1, user_interface::kBacktrack, &curr_tick_, &backtrack_tick_);
    backtrack_thd.detach();

    return false;
}

bool Aimbot::OnDisable()
{
    //clear the history
    for (int entity_id = 0; entity_id < game::kMaxPlayerNum; entity_id++)
    {
        for (int indexed_bone_id = 0; indexed_bone_id < BoneMatrix::kMaxBoneNum; indexed_bone_id++)
        {
            history_[entity_id][indexed_bone_id].clear();
        }
    }

    return false;
}

bool Aimbot::OnExecute()
{
    //checking holding a gun
    if (!weapon::IsGun(game::curr_weapon_def_index))
    {
        backtrack_tick_ = 0;
        return false;
    }

    //set up fov range
    float fov_limit = (user_interface::toggle_mode[user_interface::kAimbot] == 1 ? weapon::GetFOV(game::curr_weapon_def_index) : weapon::kRagebotFOV);

    //read the crosshair angle
    memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair_);

    //predict the bullet angle, apply recoil if viable
    bullet_ = crosshair_;
    const int weapon_type = weapon::GetWeaponType(game::curr_weapon_def_index);
    if (weapon_type == weapon::kAssaultRifle || weapon_type == weapon::kSMG || weapon_type == weapon::kMachinegun)
    {
        memory::ReadMem(module::csgo_proc_handle, game::player_address_list[game::local_player_index].GetAddress() + offsets::m_aimPunchAngle, recoil_);
        bullet_ += recoil_ * weapon::kRecoilFactor;
    }

    //calculate the maximum backtrack tick
    const int max_backtrack_tick = static_cast<int>(game::kMaxLagCompensation / game::server_info.interval_per_tick_) - 1;

#ifdef _DEBUG
    std::clog << "max backtrack tick on the curr server: " << max_backtrack_tick << '\n';
#endif

    //add target position to the aimbot candidate list
    for (int entity_id = 0; entity_id < game::kMaxPlayerNum; ++entity_id)
    {
        //filter out invalid entity 
        if (!game::player_is_valid[entity_id]) continue;

        //filter out ally
        if (game::player_list[game::local_player_index].IsAlly(game::player_list[entity_id]))
        {
            //filter out local player
            if (entity_id == game::local_player_index) continue;

            //check global targe mode
            if (user_interface::toggle_mode[user_interface::kGlobalTarget] == 0) continue;
        }

        //filter invisible enemy
        else if (user_interface::toggle_mode[user_interface::kAimbot] == 1 && !Entity::SpottedBy(entity_id, game::local_player_index)) continue;


        for (int bone_id = BoneMatrix::kBoneBegin; bone_id <= BoneMatrix::kBoneEnd; ++bone_id)
        {
            //check weapon aiming type
            if (!this->QualifyAimbotRule(bone_id)) continue;

            //calculate the relative enemy position with local playe as origin
            target_ = Position(game::bone_matrix_list[entity_id][bone_id]);

            //convert the bone index
            const int indexed_bone_id = bone_id - BoneMatrix::kBoneBegin;

            //push new backtrack if the history is empty or has a new backtrack tick
            if (history_[entity_id][indexed_bone_id].empty() ||
                history_[entity_id][indexed_bone_id].front().tick != curr_tick_)
            {
                history_[entity_id][indexed_bone_id].emplace_front(curr_tick_, target_);
            }
            else
            {
                //update the position to avoid duplicated record
                history_[entity_id][indexed_bone_id].front().pos = target_;
            }
        }
    }




    //reset the target flag, reset chosen backtrack tick
    bool has_target = false;
    int curr_backtrack_tick = 0;
    const int record_to_search = (user_interface::toggle_mode[user_interface::kBacktrack] == 1 ? max_backtrack_tick : 1);

    for (int entity_id = 0; entity_id < game::kMaxPlayerNum; ++entity_id)
    {
        //remove invalid entity
        if (!game::player_is_valid[entity_id])
        {
            for (int bone_id = BoneMatrix::kBoneBegin; bone_id <= BoneMatrix::kBoneEnd; ++bone_id)
            {
                history_[entity_id][bone_id].clear();
            }
            continue;
        }


        for (int indexed_bone_id = 0; indexed_bone_id < BoneMatrix::kMaxBoneNum; ++indexed_bone_id)
        {
            //remove expired tick
            while (!history_[entity_id][indexed_bone_id].empty())
            {
                if (history_[entity_id][indexed_bone_id].back().tick + max_backtrack_tick < curr_tick_) history_[entity_id][indexed_bone_id].pop_back();
                else break;
            }


            const int bone_id = indexed_bone_id + BoneMatrix::kBoneBegin;
            int record_searched = 0;

            for (const auto& [tick, pos] : history_[entity_id][indexed_bone_id])
            {
                //find the relative distance from the bone to local player eye
                relative_ = pos - game::player_list[game::local_player_index].GetOrigin();
                relative_.z_ -= game::player_list[game::local_player_index].GetViewOffsetZ();

                //calculate aimbot angle, find the angle difference
                exact_.PointTo(relative_);
                diff_ = exact_ - bullet_;
                diff_.Clamp();

                //calculate the multipoint radius based on bone radius and distance
                const float dist_to_enemy = relative_.MagnitudeToOrigin();
                const float multipoint_radius = Angle::ToDegrees(atan2f(BoneMatrix::kBoneRadius[bone_id], dist_to_enemy));

                //select the closest multipoint angle
                float increased_yaw = diff_.y_ + multipoint_radius;
                if (increased_yaw > 180.0f) increased_yaw -= 360.0f;
                float decreased_yaw = diff_.y_ - multipoint_radius;
                if (decreased_yaw < -180.0f) decreased_yaw += 360.0f;

                const float abs_difference_yaw = abs(diff_.y_);
                const float abs_increased_yaw = abs(increased_yaw);
                const float abs_decreased_yaw = abs(decreased_yaw);

                if (abs_increased_yaw < abs_difference_yaw && abs_increased_yaw < abs_decreased_yaw) diff_.y_ = increased_yaw;
                else if (abs_decreased_yaw < abs_difference_yaw && abs_decreased_yaw < abs_increased_yaw) diff_.y_ = decreased_yaw;


                //choose the smallest one
                const float curr_fov = diff_.FOVMagnitude();
                if (curr_fov < fov_limit)
                {
                    smallest_diff_ = diff_;
                    fov_limit = curr_fov;

                    has_target = true;
                    curr_backtrack_tick = tick;
                }

                //check searched record, no more than once without backtrack
                if (++record_searched == record_to_search) break;
            }
        }
    }


    backtrack_tick_ = curr_backtrack_tick;

    //check if selected a target
    if (!has_target) return false;

    //smooth the angle if the difference is too big
    if (user_interface::toggle_mode[user_interface::kAimbot] == 1 && fov_limit > 0.5f) smallest_diff_ /= weapon::GetSmooth(game::curr_weapon_def_index);

    //apply the angle modification
    crosshair_ += smallest_diff_;
    crosshair_.Clamp();

    //left click mouse to fire
    if (GetAsyncKeyState(0x01) & (1 << 15)) memory::WriteMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair_);

    return false;
}