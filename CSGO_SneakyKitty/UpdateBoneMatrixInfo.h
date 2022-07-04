#pragma once
#include "FeatureThread.h"

class UpdateBoneMatrixInfo : public FeatureThread
{
public:
    virtual bool OnExecute() override;
};

