#pragma once
#include "FeatureThread.h"

class Triggerbot : public FeatureThread
{
public:
    virtual bool OnExecute() override;
};

