#pragma once
#include "FeatureThread.h"

class Desync : public FeatureThread
{
    Angle client_view_{};
    Commands0X4 cmd_{};
    float real_angle_y = kYawOffset;

    static constexpr float kYawOffset = 150.0f;

public:
    virtual bool OnExecute() override;
};

