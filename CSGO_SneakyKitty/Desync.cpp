#include "Desync.h"

#include "weapon.h"


bool Desync::OnExecute()
{
    //ground, grenade, planting C4
    if (!game::player_list[game::local_player_index].IsOnGround()) return false;
    if (weapon::IsGrenade(game::curr_weapon_def_index)) return false;
    if (weapon::IsC4(game::curr_weapon_def_index) && (GetAsyncKeyState(0x01) & 1 << 15)) return false;


    if (GetAsyncKeyState('A') & 1 << 15) real_angle_y = -kYawOffset;
    else if (GetAsyncKeyState('D') & 1 << 15) real_angle_y = kYawOffset;


    const bool is_crouching = (GetAsyncKeyState(VK_CONTROL) >> 15) & 1;


    //freeze the packet queue until it matches
    memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, false);


    //wait until the cmd after the current cmd
    //there will be an unused tick between the outgoing and the incoming cmd (current cmd)
    const int incoming_cmd_num = game::last_outgoing_cmd_num + 2;

    //avoid perma disconnecting after game finishes
    while (game::connection_state == client::kFullyConnected)
    {
        int cmd_num;
        memory::ReadMem(module::csgo_proc_handle, game::net_channel + 0x18, cmd_num);
        if (cmd_num >= incoming_cmd_num) break;
    }

    //read the incoming user cmd
    memory::ReadMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, cmd_);


    //read the engine angle
    memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, cmd_.view_angles_);
    client_view_ = cmd_.view_angles_;


    //force to even tick
    cmd_.tick_count_ -= cmd_.tick_count_ % 2;


    //stop shooting during the desync
    cmd_.buttons_mask_ &= ~Input::IN_ATTACK;
    cmd_.buttons_mask_ &= ~Input::IN_ATTACK2;


    //desync angle
    cmd_.view_angles_.y_ += real_angle_y;
    cmd_.view_angles_.Clamp();


    //fakewalk
    const float real_yaw = cmd_.view_angles_.y_;


    //get moving status
    float forward_speed = 0.0f, sideway_speed = 0.0f;

    if (cmd_.buttons_mask_ & Input::IN_FORWARD) forward_speed = 449.5f;
    else if (cmd_.buttons_mask_ & Input::IN_BACK) forward_speed = -449.5f;

    if (cmd_.buttons_mask_ & Input::IN_MOVERIGHT) sideway_speed = 449.5f;
    else if (cmd_.buttons_mask_ & Input::IN_MOVELEFT) sideway_speed = -449.5f;


    //check if it is moving
    if (cmd_.buttons_mask_ & (Input::IN_FORWARD | Input::IN_BACK | Input::IN_MOVERIGHT | Input::IN_MOVELEFT))
    {
        //movement correction
        cmd_.forward_move_ = forward_speed * cosf(Angle::ToRadians(real_yaw - client_view_.y_)) +
            sideway_speed * sinf(-Angle::ToRadians(real_yaw - client_view_.y_));

        cmd_.side_move_ = forward_speed * sinf(Angle::ToRadians(real_yaw - client_view_.y_)) +
            sideway_speed * cosf(-Angle::ToRadians(real_yaw - client_view_.y_));

        //clamp the speed to avoid server side anti cheat
        cmd_.forward_move_ = std::clamp(cmd_.forward_move_, -449.5f, 449.5f);
        cmd_.side_move_ = std::clamp(cmd_.side_move_, -449.5f, 449.5f);
    }
    else
    {
        //micromovement
        if (cmd_.tick_count_ % 4 == 2) cmd_.side_move_ = (is_crouching ? 3.3f : 1.3f);
        else cmd_.side_move_ = (is_crouching ? -3.3f : -1.3f);
    }


    //write back the packet angle, unfreeze the packet
    memory::WriteMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, cmd_);
    memory::WriteMem(module::csgo_proc_handle, game::curr_verified_cmd_address + 0x4, cmd_);
    memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);

    return false;
}