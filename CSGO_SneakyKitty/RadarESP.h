#pragma once
#include "FeatureThread.h"

class RadarESP : public FeatureThread
{
public:
    virtual bool OnExecute() override;
};

