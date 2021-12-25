#include "Entity.h"


bool Entity::IsOnGround() const
{
    return this->flag_ & FL_ONGROUND;
}
bool Entity::IsDucking() const
{
    return this->flag_ & FL_DUCKING;
}
bool Entity::IsWaterJump() const
{
    return this->flag_ & FL_WATERJUMP;
}
bool Entity::IsOnTrain() const
{
    return this->flag_ & FL_ONTRAIN;
}
bool Entity::IsInRain() const
{
    return this->flag_ & FL_INRAIN;
}
bool Entity::IsFrozen() const
{
    return this->flag_ & FL_FROZEN;
}
bool Entity::IsAtControls() const
{
    return this->flag_ & FL_ATCONTROLS;
}
bool Entity::IsClient() const
{
    return this->flag_ & FL_CLIENT;
}
bool Entity::IsFakeClient() const
{
    return this->flag_ & FL_FAKECLIENT;
}
bool Entity::IsInWater() const
{
    return this->flag_ & FL_INWATER;
}
bool Entity::IsHideHudScope() const
{
    return this->flag_ & FL_HIDEHUD_SCOPE;
}



bool Entity::IsDormant() const
{
    return this->dormant_;
}
int Entity::GetHealth() const
{
    return this->health_;
}
int Entity::GetTeam() const
{
    return this->team_;
}

bool Entity::IsAlive() const
{
    return this->health_ > 0;
}

bool Entity::IsAlly(const Entity& entity)
{
    return this->team_ == entity.team_;
}