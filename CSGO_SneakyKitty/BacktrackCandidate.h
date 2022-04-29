#pragma once
#include "Position.h"

class BacktrackRecord
{
    int tick_;
    int entity_id_;
    int bone_id_;
    Position pos_;

public:

    BacktrackRecord(int new_tick, int new_entity_id, int new_bone_id, const Position& new_pos);


    bool operator==(const BacktrackRecord& rhs) const;
    bool operator<(const BacktrackRecord& rhs) const;

    int GetTick() const;
    int GetBoneID() const;
    const Position& GetPos() const;
};

