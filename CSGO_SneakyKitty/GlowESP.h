#pragma once
#include "FeatureThread.h"
#include "Cham.h"
#include "Glow.h"
#include <vector>

class GlowESP : public FeatureThread
{
    std::vector<Glow> glow_list_;
    bool is_glow_forced_ = false;
    bool is_bright_ = false;

    static constexpr Cham kTransparent{ 255, 255, 255, 255 };
    static constexpr Cham kEnemyColor{ 255, 106, 0, 255 };

public:
    virtual bool OnDisable() override;
    virtual bool OnExecute() override;
    void AdjustAmbientBrightness(float brightness);
};

