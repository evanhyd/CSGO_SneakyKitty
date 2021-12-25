#pragma once
#include "Vector3.h"

class Position final : public Vector3
{
public:

    Position() = default;
    Position(const Vector3 vec);
    Position(float new_x, float new_y, float new_z);
};

