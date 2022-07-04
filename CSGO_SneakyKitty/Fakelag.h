#pragma once
#include "FeatureThread.h"
#include "Angle.h"
#include "Position.h"

class Fakelag : public FeatureThread
{
    Angle enemy_eye_angle_{};
    Angle enemy_aimbot_angle_{};
    Angle enemy_difference_angle_{};
    Position relative_pos_{};

public:
    virtual bool OnExecute() override;
    void ChokePackets(int max_choke_ticks);
};

