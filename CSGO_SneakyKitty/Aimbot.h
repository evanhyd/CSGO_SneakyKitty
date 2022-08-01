#pragma once
#include "FeatureThread.h"
#include "Angle.h"
#include "Position.h"
#include "BacktrackRecord.h"
#include <deque>

class Aimbot : public FeatureThread
{
private:
    //target pos - local player pos
    Position target_{}, relative_{};

    //bullet = crosshair_angle + recoil_factor * recoil_angle
    Angle crosshair_{}, recoil_{}, bullet_{};

    //diff = exact - bullet
    Angle exact_{}, diff_{}, smallest_diff_{};

    std::deque<BacktrackRecord> history_[game::kMaxPlayerNum][BoneMatrix::kMaxBoneNum]{};
    
    int curr_tick_ = 0;
    int backtrack_tick_ = 0;


public:
    virtual bool OnInitialize() override;
    virtual bool OnDisable() override;
    virtual bool OnExecute() override;

    bool QualifyAimbotRule(int bone_i);
};

