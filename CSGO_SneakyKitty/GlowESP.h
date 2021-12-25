#pragma once
class GlowESP
{
public:
    void operator()(int update_period_ms);
    void AdjustAmbientBrightness(float brightness);
};

