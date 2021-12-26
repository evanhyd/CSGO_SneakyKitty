#pragma once
#include "Vector3.h"

class Position;

class Angle final : public Vector3
{
public:

    enum Direction : int
    {
        kSouthEast,
        kEast,
        kEastNorth,
        kNorth,
        kNorthWest,
        kWest,
        kWestSouth,
        kSouth
    };

    Angle() = default;
    Angle(const Vector3 & vec);
    Angle(float new_x, float new_y);
    
    //misc
    void Clamp();
    float FOVMagnitude() const;
    int GetDirection() const;
    void PointTo(const Position& pos);

    static constexpr float kPi = 3.1415926535f;
    static constexpr float kRadian = 57.2957795130f;
    static float ToDegrees(float radians);
    static float ToRadians(float degrees);

    /*

	void ToClosestMultipoint(float radius);

	
	static float CalcMultipointRadius(int bone_index, float distance);
    */
    
};

