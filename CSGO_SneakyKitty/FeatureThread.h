#pragma once
#include "game.h"
#include "module.h"
#include "offsets.h"
#include "memory.h"
#include "user_interface.h"

#include <iostream>
#include <thread>
#include <chrono>

class FeatureThread
{
private:
    int disable_ms_;
    int enable_ms_;
    int hotkey_;

public:
    virtual void operator()(int disable_ms, int enable_ms, int hotkey);

protected:
    virtual bool OnInitialize();
    virtual bool OnDisable();
    virtual bool OnExecute();
};

