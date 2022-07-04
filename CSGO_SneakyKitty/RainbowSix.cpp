#include "RainbowSix.h"

bool RainbowSix::OnExecute()
{
    //read the crosshair angle
    memory::ReadMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair_);

    if (GetAsyncKeyState('Q')) crosshair_.z_ -= kPeekSpeed;
    else if (GetAsyncKeyState('E')) crosshair_.z_ += kPeekSpeed;
    else
    {
        if (crosshair_.z_ < -kPeekSpeed - 0.5f) crosshair_.z_ += kPeekSpeed;
        else if (crosshair_.z_ > kPeekSpeed + 0.5f) crosshair_.z_ -= kPeekSpeed;
        else crosshair_.z_ = 0.0f;
    }

    crosshair_.Clamp();
    memory::WriteMem(module::csgo_proc_handle, game::client_state + offsets::dwClientState_ViewAngles, crosshair_);

    return false;
}