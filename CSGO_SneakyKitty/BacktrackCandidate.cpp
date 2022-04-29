#include "BacktrackCandidate.h"

BacktrackRecord::BacktrackRecord(int new_tick, int new_entity_id, int new_bone_id, const Position& new_pos) : 
    tick_(new_tick), entity_id_(new_entity_id), bone_id_(new_bone_id), pos_(new_pos)
{
    //empty
}

bool BacktrackRecord::operator==(const BacktrackRecord& rhs) const
{
    return tick_ == rhs.tick_ && entity_id_ == rhs.entity_id_ && bone_id_ == rhs.bone_id_;
}

bool BacktrackRecord::operator<(const BacktrackRecord& rhs) const
{
    return tick_ < rhs.tick_ || 
           tick_ == rhs.tick_ && entity_id_ < rhs.entity_id_ || 
           tick_ == rhs.tick_ && entity_id_ == rhs.entity_id_ && bone_id_ < rhs.bone_id_;
}

int BacktrackRecord::GetTick() const
{
    return this->tick_;
}
int BacktrackRecord::GetBoneID() const
{
    return this->bone_id_;
}
const Position& BacktrackRecord::GetPos() const
{
    return this->pos_;
}