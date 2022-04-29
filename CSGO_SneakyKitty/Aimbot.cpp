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

#include <iostream>
#include <thread>
#include <chrono>
#include <deque>
#include <map>

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
    Position enemy{};
    Position relative{};

    //bullet = crosshair_angle + recoil_factor * recoil_angle
    Angle crosshair{};
    Angle recoil{};
    Angle bullet{};

    //difference = exact - bullet
    Angle exact{};
    Angle difference{};
    Angle closest{};


    //std::deque<BacktrackRecord> history;
    std::map<BacktrackRecord, Position> history;


    int curr_tick = 0;
    int backtrack_tick = 0;
    std::thread backtrack_thd(Backtrack(), 1, std::ref(curr_tick), std::ref(backtrack_tick));
    backtrack_thd.detach();
    

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || game::toggle_mode[game::aimbot_fire_hotkey] == 0)
        {
            if (!history.empty()) history.clear();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        if (weapon::IsGun(game::curr_weapon_def_index))
        {
            //reset the lower bound, obtain the weapon fov
            bool has_target = false;
            float fov_limit = (game::toggle_mode[game::aimbot_fire_hotkey] == 1 ? weapon::GetFOV(game::curr_weapon_def_index) : weapon::kRagebotFOV);


            //read the crosshair angle
            memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair);
            bullet = crosshair;


            //apply recoil if viable
            const int weapon_type = weapon::GetWeaponType(game::curr_weapon_def_index);
            if (weapon_type == weapon::kAssaultRifle || weapon_type == weapon::kSMG || weapon_type == weapon::kMachinegun)
            {
                memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[game::local_player_index].GetAddress() + offsets::m_aimPunchAngle, recoil);
                bullet += recoil * weapon::kRecoilFactor;
            }


            //calculate the maximum backtrack tick
            const int max_backtrack_tick = static_cast<int>(client::kMaxLagCompensation / game::server_info.interval_per_tick_) - 1;

            //std::cout << "max: " << max_backtrack_tick << '\n';

            //aimbot 
            for (int entity_id = 0; entity_id < client::kMaxPlayerNum; ++entity_id)
            {
                //filter out invalid entity 
                if (!game::player_entity_is_valid[entity_id]) continue;


                //filter out ally
                if (game::player_entity_list[game::local_player_index].IsAlly(game::player_entity_list[entity_id]))
                {
                    //filter out local player
                    if (entity_id == game::local_player_index) continue;

                    //check global targe mode
                    if (game::toggle_mode[game::global_target_hotkey] == 0) continue;
                }
                else
                //check visibility
                if (!Entity::SpottedBy(entity_id, game::local_player_index))
                {
                    //check legit aimbot mode
                    if (game::toggle_mode[game::aimbot_fire_hotkey] == 1) continue;
                }
                

                for (int bone_id = BoneMatrix::kBoneBegin; bone_id <= BoneMatrix::kBoneEnd; ++bone_id)
                {
                    //check weapon aiming type
                    if (!this->QualifyAimbotRule(bone_id)) continue;


                    //calculate the relative enemy position with local playe as origin
                    enemy = Position(game::bone_matrix_list[entity_id][bone_id]);


                    //add to the backtrack candidates
                    if (game::toggle_mode[game::aimbot_backtrack_hotkey] == 1) 
                    {
                        //#1. always add, slow and bloated size
                        //history.push_back(BacktrackRecord(curr_tick, entity_id, bone_id, enemy));


                        //#2. binary search only, misses shots really often
                        //const BacktrackRecord pos_record(curr_tick, entity_id, bone_id, enemy);
                        //const bool has_record = std::binary_search(history.begin(), history.end(), pos_record);
                        //if (!has_record) history.push_back(pos_record);


                        //#3. binary search with update, relatively more reliable, but fk up the input may not be ordered
                        //const BacktrackRecord pos_record(curr_tick, entity_id, bone_id, enemy);
                        //auto res = std::lower_bound(history.begin(), history.end(), pos_record);
                        //if (res == history.end() || *res != pos_record) history.push_back(pos_record); //found new record 
                        //else *res = pos_record; //update old record


                        //#4. using binary search tree from std::map, slower insertion time and deletion time, but stable and correct result
                        const BacktrackRecord pos_record(curr_tick, entity_id, bone_id);
                        history.insert_or_assign(pos_record, enemy);
                    }


                    //bullets shoot from player's eyes, subtract the relative height
                    relative = enemy - game::player_entity_list[game::local_player_index].GetOrigin();
                    relative.z_ -= game::player_entity_list[game::local_player_index].GetViewOffsetZ();


                    //calculate the exact aimbot angle
                    exact.PointTo(relative);


                    //calculate the difference between the exact and the bullet
                    difference = exact - bullet;
                    difference.Clamp();


                    //calculate multipoint radius
                    float dist_to_enemy = relative.MagnitudeToOrigin();
                    float multipoint_radius = Angle::ToDegrees(atan2f(BoneMatrix::kBoneRadius[bone_id], dist_to_enemy));


                    //calculate the multipoint based on the radius
                    //here only applies horizontal multipoint 
                    float increased_yaw = difference.y_ + multipoint_radius;
                    if (increased_yaw > 180.0f) increased_yaw -= 360.0f;

                    float decreased_yaw = difference.y_ - multipoint_radius;
                    if (decreased_yaw < -180.0f) decreased_yaw += 360.0f;

                    if (abs(increased_yaw) < abs(difference.y_) && abs(increased_yaw) < abs(decreased_yaw)) difference.y_ = increased_yaw;
                    else if(abs(decreased_yaw) < abs(difference.y_) && abs(decreased_yaw) < abs(increased_yaw)) difference.y_ = decreased_yaw;


                    float curr_fov = difference.FOVMagnitude();
                    if (curr_fov < fov_limit)
                    {
                        closest = difference;
                        fov_limit = curr_fov;
                        has_target = true;
                    }
                }
            }


            if (game::toggle_mode[game::aimbot_backtrack_hotkey] == 1)
            {
                int best_backtrack_tick = 0;

                //remove old ticks
                //std::clog << history.size() << '\n';
                auto last_invalid_record_iter = history.upper_bound(BacktrackRecord(curr_tick - max_backtrack_tick, client::kMaxPlayerNum, BoneMatrix::kBoneEnd));
                history.erase(history.begin(), last_invalid_record_iter);

                //select the best backtrack tick
                for (const auto& [record, pos] : history)
                {
                    relative = pos - game::player_entity_list[game::local_player_index].GetOrigin();
                    relative.z_ -= game::player_entity_list[game::local_player_index].GetViewOffsetZ();
                    exact.PointTo(relative);
                    difference = exact - bullet;
                    difference.Clamp();

                    float dist_to_enemy = relative.MagnitudeToOrigin();
                    float multipoint_radius = Angle::ToDegrees(atan2f(BoneMatrix::kBoneRadius[record.GetBoneID()], dist_to_enemy));

                    float increased_yaw = difference.y_ + multipoint_radius;
                    if (increased_yaw > 180.0f) increased_yaw -= 360.0f;
                    float decreased_yaw = difference.y_ - multipoint_radius;
                    if (decreased_yaw < -180.0f) decreased_yaw += 360.0f;
                    if (abs(increased_yaw) < abs(difference.y_) && abs(increased_yaw) < abs(decreased_yaw)) difference.y_ = increased_yaw;
                    else if (abs(decreased_yaw) < abs(difference.y_) && abs(decreased_yaw) < abs(increased_yaw)) difference.y_ = decreased_yaw;


                    //choose the smallest one
                    float curr_fov = difference.FOVMagnitude();
                    if (curr_fov < fov_limit)
                    {
                        best_backtrack_tick = record.GetTick();
                        closest = difference;
                        fov_limit = curr_fov;
                        has_target = true;
                    }
                }

                backtrack_tick = best_backtrack_tick;
            }
            else
            {
                backtrack_tick = 0;
            }


            if (!has_target) continue;

            //smooth the aimbot if legit and no backtrack
            if (game::toggle_mode[game::aimbot_fire_hotkey] == 1 && backtrack_tick == 0) closest /= weapon::GetSmooth(game::curr_weapon_def_index);

            //apply the angle modification
            crosshair += closest;
            crosshair.Clamp();

            if (GetAsyncKeyState(0x01) & 1 << 15)
            {
                memory::WriteMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}
