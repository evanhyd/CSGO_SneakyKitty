#include "BacktrackCandidate.h"

BacktrackCandidate::BacktrackCandidate(int new_tick, int new_bone_id, const Position& new_pos) : tick_(new_tick), bone_id_(new_bone_id), pos_(new_pos)
{
    //empty
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