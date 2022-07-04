#pragma once
#include "FeatureThread.h"

class UpdateEntityInfo : public FeatureThread
{
public:
    virtual bool OnExecute() override;
};

