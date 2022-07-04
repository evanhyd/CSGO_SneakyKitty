#pragma once
#include "FeatureThread.h"
#include "Input.h"

class Backtrack : public FeatureThread
{
    const int* backtrack_tick_ = nullptr;
    int* current_tick_ = nullptr;
    Commands0X4 cmd_{};

public:

    void operator()(int disable_ms, int enable_ms, int hotkey, int* curr_tick, const int* const backtrack_tick);
    virtual bool OnExecute() override;
};

