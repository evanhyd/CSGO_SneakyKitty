#pragma once
#include "FeatureThread.h"

class UpdateClientInfo : public FeatureThread
{
public:
    virtual bool OnExecute() override;
};

