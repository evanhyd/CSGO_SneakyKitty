#include "Backtrack.h"

#include "weapon.h"

using namespace user_interface;

void Backtrack::operator()(int disable_ms, int enable_ms, int hotkey, int* curr_tick, const int* const backtrack_tick)
{
    this->current_tick_ = curr_tick;
    this->backtrack_tick_ = backtrack_tick;

    this->FeatureThread::operator()(disable_ms, enable_ms, hotkey);
}

bool Backtrack::OnExecute()
{
    //moving + freezing packet causes teleport, sus as fk
    if (!GetAsyncKeyState(0x01))
    {
        if (GetAsyncKeyState('W') & 1 << 15 || GetAsyncKeyState('S') & 1 << 15 || GetAsyncKeyState('A') & 1 << 15 || GetAsyncKeyState('D') & 1 << 15)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            return false;
        }
    }


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

    //update the current tick
    *current_tick_ = cmd_.tick_count_;

    //detect mouse left click
    if (GetAsyncKeyState(0x01) & (1 << 15))
    {
        const int chosen_tick = *backtrack_tick_;
        if (chosen_tick > 0)
        {
            //apply backtrack
            cmd_.buttons_mask_ |= Input::IN_ATTACK;
            if (GetAsyncKeyState(VK_CONTROL) & 1 << 15) cmd_.buttons_mask_ |= Input::IN_DUCK;
            cmd_.tick_count_ = chosen_tick;

            memory::WriteMem(module::csgo_proc_handle, game::curr_cmd_address + 0x4, cmd_);
            memory::WriteMem(module::csgo_proc_handle, game::curr_verified_cmd_address + 0x4, cmd_);
        }
        else
        {
            memory::WriteMem(module::csgo_proc_handle, module::client_dll + offsets::dwForceAttack, 6);
        }
    }

    memory::WriteMem(module::csgo_proc_handle, module::engine_dll + offsets::dwbSendPackets, true);
    return false;
}