#include "Angle.h"
#include <cmath>

Angle::Angle(float new_x, float new_y) : Vector3(new_x, new_y, 0.0f)
{
	//empty
}


float Angle::MagnitudeToCrosshair() const
{
	return hypotf(this->x_, this->y_);
}

void Angle::Clamp()
{
	if (this->x_ > 89.0f) this->x_ = 89.0f;
	if (this->x_ < -89.0f) this->x_ = -89.0f;

	while (this->y_ > 180.0f) this->y_ -= 360.0f;
	while (this->y_ < -180.0f) this->y_ += 360.0f;
}

int Angle::GetDirection() const
{
	if (this->y_ >= -157.5f && this->y_ < -112.5f) return Direction::kSouthEast;
	if (this->y_ >= -112.5f && this->y_ < -67.5f) return Direction::kEast;
	if (this->y_ >= -67.5f && this->y_ < -22.5f) return Direction::kEastNorth;
	if (this->y_ >= -22.5f && this->y_ < 22.5f) return Direction::kNorth;
	if (this->y_ >= 22.5f && this->y_ < 67.5f) return Direction::kNorthWest;
	if (this->y_ >= 67.5f && this->y_ < 112.5f) return Direction::kWest;
	if (this->y_ >= 112.5f && this->y_ < 157.5f) return Direction::kWestSouth;
	else return Direction::kSouth;
}

void Angle::PointTo(const Position& pos)
{
	
}




/*

void Angle::SetToVector3(const Vector3& relativePos)
{
	//atan2 gives x_ in radians, where x_ in degrees -180 < x_ < 180
	this->y = Angle::ToDegrees(atan2f(relativePos.y, relativePos.x));

	float hypotenuse = hypotf(relativePos.y, relativePos.x);

	//x_ is pitch, and it is upside down
	this->x = -Angle::ToDegrees(atan2f(relativePos.z, hypotenuse));
}

void Angle::ToClosestMultipoint(float radius)
{

		0 1 2
		3 4 5
		6 7 8


	float increase_x = this->x + radius;
	if (increase_x > 180.0f) increase_x -= 360.0f;

	float decrease_x = this->x - radius;
	if (increase_x < -180.0f) increase_x += 360.0f;

	//find the minimum magnitude
	if (abs(increase_x) < abs(this->x) && abs(increase_x) < abs(decrease_x)) this->x = increase_x;
	else if (abs(decrease_x) < abs(this->x) && abs(decrease_x) < abs(increase_x)) this->x = decrease_x;
}


float Angle::ToDegrees(float radians)
{
	return radians * 180.0f / PI;
}

float Angle::ToRadians(float degrees)
{
	return degrees * PI / 180.0f;
}

float Angle::CalcMultipointRadius(int bone_index, float distance)
{
	return Angle::ToDegrees(atan2f(Bone::BONE_RADIUS[bone_index], distance));
}
*/