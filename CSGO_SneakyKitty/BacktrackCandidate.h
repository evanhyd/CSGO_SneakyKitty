#pragma once
#include "Position.h"

class BacktrackCandidate
{
    int tick_;
    int bone_id_;
    Position pos_;

public:

    BacktrackCandidate(int new_tick, int new_bone_id, const Position& new_pos);

    int GetTick() const;
    int GetBoneID() const;
    const Position& GetPos() const;
};

