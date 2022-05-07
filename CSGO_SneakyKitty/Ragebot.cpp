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
    int target_id = -1;

    std::thread ragebot_thd(Ragebot::Packet(), update_period_ms, std::ref(target_id), std::ref(ragebot));
    ragebot_thd.detach();

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kRagebot] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        //checking holding a gun
        if (!weapon::IsGun(game::curr_weapon_def_index))
        {
            target_id = -1;
            continue;
        }


        //obtain the recoil
        const int weapon_type = weapon::GetWeaponType(game::curr_weapon_def_index);
        if (weapon_type == weapon::kAssaultRifle || weapon_type == weapon::kSMG || weapon_type == weapon::kMachinegun || weapon_type == weapon::kPistol)
        {
            memory::ReadMem(module::csgo_proc_handle, game::player_entity_address_list[game::local_player_index].GetAddress() + offsets::m_aimPunchAngle, recoil);
        }
        else
        {
            recoil = { 0.0f, 0.0f };
        }

        //select the closest target
        int curr_target_id = -1;
        double curr_target_dist = 9999999999999999.0;
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
            if (dist_to_enemy < curr_target_dist)
            {
                //calculate the exact aimbot angle
                exact.PointTo(relative);

                curr_target_id = entity_id;
                curr_target_dist = dist_to_enemy;
            }
        }

        //update
        target_id = curr_target_id;
        ragebot = exact - recoil * weapon::kRecoilFactor;

        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}


void Ragebot::Packet::operator()(int update_period_ms, int& best_target_id, const Angle& ragebot)
{
    Angle client_view{};
    Commands0X4 cmd;

    while (true)
    {
        if (game::connection_state != client::kFullyConnected || toggle_mode[kRagebot] == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            continue;
        }

        //grenade, planting C4
        if (weapon::IsGrenade(game::curr_weapon_def_index) && weapon::IsC4(game::curr_weapon_def_index)) continue;

        //get moving status
        float moving_forward = 0.0f, moving_sideway = 0.0f;
        if (GetAsyncKeyState('W') & 1 << 15) moving_forward = 449.5f;
        else if (GetAsyncKeyState('S') & 1 << 15) moving_forward = -449.5f;

        if (GetAsyncKeyState('D') & 1 << 15) moving_sideway = 449.5f;
        else if (GetAsyncKeyState('A') & 1 << 15) moving_sideway = -449.5f;


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
        memory::ReadMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, cmd);


        //fix crouching
        if (is_crouching) cmd.buttons_mask_ |= Input::IN_DUCK;


        //no target, perform antiaim
        if (best_target_id != -1)
        {
            //force fire
            cmd.buttons_mask_ |= Input::IN_ATTACK;

            //apply ratebot angle
            cmd.view_angles_ = ragebot;


            //fix movement
            memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, client_view);
            cmd.forward_move_ = moving_forward * cosf(Angle::ToRadians(ragebot.y_ - client_view.y_)) +
                                         moving_sideway * sinf(-Angle::ToRadians(ragebot.y_ - client_view.y_));

            cmd.side_move_ = moving_forward * sinf(Angle::ToRadians(ragebot.y_ - client_view.y_)) +
                                      moving_sideway * cosf(-Angle::ToRadians(ragebot.y_ - client_view.y_));


            //clamp the speed to avoid server side anti cheat
            cmd.forward_move_ = std::clamp(cmd.forward_move_, -449.5f, 449.5f);
            cmd.side_move_ = std::clamp(cmd.side_move_, -449.5f, 449.5f);
        }


        //disable due to ladder bug, too lazy to fix it
        ////sliding
        //else
        //{
        //    cmd.forward_move_ = moving_forward;
        //    cmd.side_move_ = moving_sideway;

        //    //moon walk
        //    if (cmd.forward_move_ > 5.0f)
        //    {
        //        cmd.buttons_mask_ &= ~Input::IN_FORWARD;
        //        cmd.buttons_mask_ |= Input::IN_BACK;
        //    }
        //    else if (cmd.forward_move_ < -5.0f)
        //    {
        //        cmd.buttons_mask_ &= ~Input::IN_BACK;
        //        cmd.buttons_mask_ |= Input::IN_FORWARD;
        //    }

        //    if (cmd.side_move_ > 5.0f)
        //    {
        //        cmd.buttons_mask_ &= ~Input::IN_MOVERIGHT;
        //        cmd.buttons_mask_ |= Input::IN_MOVELEFT;
        //    }
        //    else if (cmd.side_move_ < -5.0f)
        //    {
        //        cmd.buttons_mask_ &= ~Input::IN_MOVELEFT;
        //        cmd.buttons_mask_ |= Input::IN_MOVERIGHT;
        //    }
        //}


        memory::WriteMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, cmd);
        memory::WriteMem(module::csgo_proc_handle, game::curr_verified_cmd_address + 0x4, cmd);
        memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);
        std::this_thread::sleep_for(std::chrono::milliseconds(update_period_ms));
    }
}