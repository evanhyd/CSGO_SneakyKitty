#pragma once
#include "FeatureThread.h"
#include "Angle.h"

class RainbowSix : public FeatureThread
{
    Angle crosshair_{};

    static constexpr float kPeekSpeed = 4.0f;

public:
    virtual bool OnExecute() override;
};

