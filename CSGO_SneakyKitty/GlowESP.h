#pragma once
#include "Cham.h"

class GlowESP
{
public:
    void operator()(int update_period_ms, float brightness, Cham enemy_model_color);
    void AdjustAmbientBrightness(float brightness);
};

