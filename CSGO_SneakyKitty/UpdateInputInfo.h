#pragma once
#include "FeatureThread.h"

class UpdateInputInfo : public FeatureThread
{
public:
    virtual bool OnExecute() override;
};

