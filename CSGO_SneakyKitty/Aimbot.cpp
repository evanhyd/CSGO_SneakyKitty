#include "Aimbot.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "Angle.h"
#include "Position.h"
#include "weapon.h"
#include "Backtrack.h"
#include "BacktrackCandidate.h"
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
    //enemy pos - local player pos
    Position enemy{}, relative{};

    //bullet = crosshair_angle + recoil_factor * recoil_angle
    Angle crosshair{}, recoil{}, bullet{};

    //difference = exact - bullet
    Angle exact{}, difference{}, closest{};


    //std::deque<BacktrackRecord> history;
    std::map<BacktrackRecord, Position> history;


    int curr_tick = 0;
    int backtrack_tick = 0;
    std::thread backtrack_thd(Backtrack(), 1, std::ref(curr_tick), std::ref(backtrack_tick));
    backtrack_thd.detach();
    

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kAimbot] == 0)
        {
            if (!history.empty()) history.clear();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        //checking holding a gun
        if (!weapon::IsGun(game::curr_weapon_def_index))
        {
            backtrack_tick = 0;
            continue;
        }
        

        //fov upper bound
        float fov_limit = (toggle_mode[kAimbot] == 1 ? weapon::GetFOV(game::curr_weapon_def_index) : weapon::kRagebotFOV);


        //read the crosshair angle
        memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair);


        //predict the bullet angle, apply recoil if viable
        bullet = crosshair;
        const int weapon_type = weapon::GetWeaponType(game::curr_weapon_def_index);
        if (weapon_type == weapon::kAssaultRifle || weapon_type == weapon::kSMG || weapon_type == weapon::kMachinegun)
        {
            memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[game::local_player_index].GetAddress() + offsets::m_aimPunchAngle, recoil);
            bullet += recoil * weapon::kRecoilFactor;
        }


        //calculate the maximum backtrack tick
        const int max_backtrack_tick = static_cast<int>(client::kMaxLagCompensation / game::server_info.interval_per_tick_) - 1;

#ifdef _DEBUG
        std::clog << "max backtrack tick: " << max_backtrack_tick << '\n';
#endif

        //add target position to the aimbot candidate list
        for (int entity_id = 0; entity_id < client::kMaxPlayerNum; ++entity_id)
        {
            //filter out invalid entity 
            if (!game::player_entity_is_valid[entity_id]) continue;

            //filter out ally
            if (game::player_entity_list[game::local_player_index].IsAlly(game::player_entity_list[entity_id]))
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
                enemy = Position(game::bone_matrix_list[entity_id][bone_id]);

                //using binary search tree from std::map, slower insertion time and deletion time, but stable and correct result
                history.insert_or_assign(BacktrackRecord(curr_tick, entity_id, bone_id), enemy);
            }
        }



        //remove old ticks
        auto last_invalid_record_iter = history.upper_bound(BacktrackRecord(curr_tick - max_backtrack_tick, client::kMaxPlayerNum, BoneMatrix::kBoneEnd));
        history.erase(history.begin(), last_invalid_record_iter);


        //remove invalid/dead players
        /*for (auto entry = history.begin(); entry != history.end();)
        {
            if (!game::player_entity_is_valid[entry->first.GetEntityID()]) entry = history.erase(entry);
            else ++entry;
        }*/


        //reset the target flag, best backtrack tick
        bool has_target = false;
        int curr_backtrack_tick = 0;
        int enemy_searched = 0;

        for (auto entry = history.cbegin(); entry != history.cend();)
        {
            //compiler should optimize it out
            const BacktrackRecord& record = entry->first;
            const Position& pos = entry->second;

            //ignore invalid/dead entity
            if (!game::player_entity_is_valid[record.GetEntityID()])
            {
                entry = history.erase(entry);
                continue;
            }

            //stop seraching if no backtrack
            if (++enemy_searched > client::kMaxPlayerNum && toggle_mode[kBacktrack] == 0) break;

            //bullets shoot from player's eyes, subtract the relative height
            relative = pos - game::player_entity_list[game::local_player_index].GetOrigin();
            relative.z_ -= game::player_entity_list[game::local_player_index].GetViewOffsetZ();

            //calculate the exact aimbot angle and difference
            exact.PointTo(relative);
            difference = exact - bullet;
            difference.Clamp();

            //calculate the multipoint radius
            const float dist_to_enemy = relative.MagnitudeToOrigin();
            const float multipoint_radius = Angle::ToDegrees(atan2f(BoneMatrix::kBoneRadius[record.GetBoneID()], dist_to_enemy));

            //select the closest multipoint angle
            float increased_yaw = difference.y_ + multipoint_radius;
            if (increased_yaw > 180.0f) increased_yaw -= 360.0f;
            float decreased_yaw = difference.y_ - multipoint_radius;
            if (decreased_yaw < -180.0f) decreased_yaw += 360.0f;

            const float abs_difference_yaw = abs(difference.y_);
            const float abs_increased_yaw = abs(increased_yaw);
            const float abs_decreased_yaw = abs(decreased_yaw);

            if (abs_increased_yaw < abs_difference_yaw && abs_increased_yaw < abs_decreased_yaw) difference.y_ = increased_yaw;
            else if (abs_decreased_yaw < abs_difference_yaw && abs_decreased_yaw < abs_increased_yaw) difference.y_ = decreased_yaw;


            //choose the smallest one
            const float curr_fov = difference.FOVMagnitude();
            if (curr_fov < fov_limit)
            {
                closest = difference;
                fov_limit = curr_fov;

                has_target = true;
                curr_backtrack_tick = record.GetTick();
            }

            ++entry;
        }
        backtrack_tick = curr_backtrack_tick;

        //check if selected a target
        if (!has_target) continue;

        //legit aimbot smooth aim step
        if (toggle_mode[kAimbot] == 1) closest /= weapon::GetSmooth(game::curr_weapon_def_index);

        //apply the angle modification
        crosshair += closest;
        crosshair.Clamp();

        //left click mouse to fire
        if (GetAsyncKeyState(0x01) & 1 << 15) memory::WriteMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair);

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}



//ragebot incompatiable with aimbot, backtrack, desync
//aimbot 2 incompatiable with backtrack