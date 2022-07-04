#pragma once
#include "FeatureThread.h"

class UpdateWeaponInfo : public FeatureThread
{
public:
    virtual bool OnExecute() override;
};

