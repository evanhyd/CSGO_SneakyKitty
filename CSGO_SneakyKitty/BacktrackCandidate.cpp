#include "BacktrackCandidate.h"

BacktrackCandidate::BacktrackCandidate(int new_tick, int new_entity_id, int new_bone_id, const Position& new_pos) : 
    tick_(new_tick), entity_id_(new_entity_id), bone_id_(new_bone_id), pos_(new_pos)
{
    //empty
}

bool BacktrackCandidate::operator==(const BacktrackCandidate& rhs) const
{
    return tick_ == rhs.tick_ && entity_id_ == rhs.entity_id_ && bone_id_ == rhs.bone_id_;
}

bool BacktrackCandidate::operator<(const BacktrackCandidate& rhs) const
{
    return tick_ < rhs.tick_ || 
           tick_ == rhs.tick_ && entity_id_ < rhs.entity_id_ || 
           tick_ == rhs.tick_ && entity_id_ == rhs.entity_id_ && bone_id_ < rhs.bone_id_;
}

int BacktrackCandidate::GetTick() const
{
    return this->tick_;
}
int BacktrackCandidate::GetBoneID() const
{
    return this->bone_id_;
}
const Position& BacktrackCandidate::GetPos() const
{
    return this->pos_;
}