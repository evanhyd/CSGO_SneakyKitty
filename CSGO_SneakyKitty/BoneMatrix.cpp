#include "BoneMatrix.h"
#include "Position.h"


BoneMatrix::operator Position() const
{
    return Position(this->x_, this->y_, this->z_);
}