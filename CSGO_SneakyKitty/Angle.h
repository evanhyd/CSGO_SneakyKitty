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

    Angle(float new_x, float new_y);
    
    //misc
    void Clamp();
    float MagnitudeToCrosshair() const;
    int GetDirection() const;
    void PointTo(const Position& pos);

    /*
    
	void SetToVector3(const Vector3& relativePos);

	void ToClosestMultipoint(float radius);

	static constexpr float PI = 3.141592653589793f;
	static float ToDegrees(float radians);
	static float ToRadians(float degrees);
	static float CalcMultipointRadius(int bone_index, float distance);
    */
    
};

