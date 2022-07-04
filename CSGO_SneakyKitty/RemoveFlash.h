#pragma once
#include "FeatureThread.h"

class RemoveFlash : public FeatureThread
{
public:
    virtual bool OnExecute() override;
};

