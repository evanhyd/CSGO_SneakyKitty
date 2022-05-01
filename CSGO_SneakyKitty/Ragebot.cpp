#include "Ragebot.h"

#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "Angle.h"
#include "Position.h"
#include "weapon.h"
#include "user_interface.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <deque>
#include <map>

using namespace user_interface;

void Ragebot::operator()(int update_period_ms)
{
    //enemy pos - local player pos
    Position enemy{}, relative{};

    //ragebot = exact - recoil
    Angle recoil{}, exact{}, ragebot{};
    int best_target_id = -1;

    std::thread ragebot_thd(Ragebot::Packet(), update_period_ms, std::ref(best_target_id), std::ref(ragebot));
    ragebot_thd.detach();

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kRagebot] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }


        //checking holding a gun
        if (!weapon::IsGun(game::curr_weapon_def_index)) continue;


        //obtain the recoil
        const int weapon_type = weapon::GetWeaponType(game::curr_weapon_def_index);
        if (weapon_type == weapon::kAssaultRifle || weapon_type == weapon::kSMG || weapon_type == weapon::kMachinegun)
        {
            memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[game::local_player_index].GetAddress() + offsets::m_aimPunchAngle, recoil);
        }
        else
        {
            recoil = { 0.0f, 0.0f };
        }


        int target_id = -1;
        double target_dist = 9999999999999999.0;

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


            //filter out invisible enemy
            else if (!Entity::SpottedBy(entity_id, game::local_player_index) && !Entity::SpottedBy(game::local_player_index, entity_id)) continue;


            //calculate the relative enemy head position with local player's head as origin
            enemy = Position(game::bone_matrix_list[entity_id][BoneMatrix::kBoneEnd]);
            relative = enemy - game::player_entity_list[game::local_player_index].GetOrigin();
            relative.z_ -= game::player_entity_list[game::local_player_index].GetViewOffsetZ();


            //select the closest enemy
            double dist_to_enemy = relative.MagnitudeToOrigin();
            if (dist_to_enemy < target_dist)
            {
                //calculate the exact aimbot angle
                exact.PointTo(relative);

                target_id = entity_id;
                target_dist = dist_to_enemy;
            }
        }

        //update
        best_target_id = target_id;
        ragebot = exact - weapon::kRecoilFactor * recoil;

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}


void Ragebot::Packet::operator()(int update_period_ms, int& best_target_id, const Angle& ragebot)
{
    Commands0X4 commands_0x4;

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kRagebot] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        //ground, grenade, planting C4
        if (!game::player_entity_list[game::local_player_index].IsOnGround()) continue;
        if (weapon::IsGrenade(game::curr_weapon_def_index)) continue;
        if (weapon::IsC4(game::curr_weapon_def_index) && (GetAsyncKeyState(0x01) & 1 << 15)) continue;


        //get crouching status
        bool is_crouching = ((GetAsyncKeyState(VK_CONTROL) & 1 << 15) ? true : false);


        //freeze the packet queue until it matches
        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, false);


        //wait until the cmd after the current cmd
        //there will be an unused tick between the outgoing and the incoming cmd (current cmd)
        int incoming_cmd_num = game::last_outgoing_cmd_num + 2;

        //avoid perma disconnecting after game finishes
        while (game::connection_state == client::kFullyConnected)
        {
            int cmd_num;
            memory::ReadMem(module::csgo_proc_handle, game::net_channel + 0x18, cmd_num);
            if (cmd_num >= incoming_cmd_num) break;
        }

        //read the incoming user cmd
        memory::ReadMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, commands_0x4);


        //fix crouching
        if (is_crouching) commands_0x4.buttons_mask_ |= Input::IN_DUCK;


        //no target, perform antiaim
        if (best_target_id != -1)
        {
            commands_0x4.buttons_mask_ |= Input::IN_ATTACK;
            commands_0x4.view_angles_ = ragebot;
            memory::WriteMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, commands_0x4);
            memory::WriteMem(module::csgo_proc_handle, game::curr_verified_cmd_address + 0x4, commands_0x4);
        }

        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);
        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}