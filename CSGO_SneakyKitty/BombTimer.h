#pragma once
#include "FeatureThread.h"

class BombTimer : public FeatureThread
{
public:
    virtual bool OnExecute() override;
};

