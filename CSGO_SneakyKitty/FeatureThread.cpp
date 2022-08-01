#include "FeatureThread.h"

void FeatureThread::operator()(int disable_ms, int enable_ms, int hotkey)
{
    //thread sleeping time
    this->disable_ms_ = disable_ms;
    this->enable_ms_ = enable_ms;
    this->hotkey_ = hotkey;

    //one time set up
    OnInitialize();

    while (true)
    {
        //connection + hotkey check
        if (this->hotkey_ != user_interface::kCore)
        {
            if (game::connection_state != game::kFullyConnected || user_interface::toggle_mode[this->hotkey_] == 0)
            {
                OnDisable();
                std::this_thread::sleep_for(std::chrono::milliseconds(this->disable_ms_));
                continue;
            }
        }
        

        //core function
        OnExecute();

        //post sleeping
        std::this_thread::sleep_for(std::chrono::milliseconds(this->enable_ms_));
    }
}

bool FeatureThread::OnInitialize()
{
    return false;
}
bool FeatureThread::OnDisable()
{
    return false;
}
bool FeatureThread::OnExecute()
{
    return false;
}