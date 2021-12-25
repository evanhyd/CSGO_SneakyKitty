#include "Entity.h"


bool Entity::IsAlly(const Entity& entity)
{
    return this->team_ == entity.team_;
}