#include "Vector3.h"
#include <cmath>

Vector3::Vector3(float new_x, float new_y, float new_z) : x_(new_x), y_(new_y), z_(new_z)
{
	//empty
}

Vector3& Vector3::operator+=(const Vector3& addend)
{
	this->x_ += addend.x_;
	this->y_ += addend.y_;
	this->z_ += addend.z_;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& subtrahend)
{
	this->x_ -= subtrahend.x_;
	this->y_ -= subtrahend.y_;
	this->z_ -= subtrahend.z_;

	return *this;
}
Vector3& Vector3::operator*=(float multiplier)
{
	this->x_ *= multiplier;
	this->y_ *= multiplier;
	this->z_ *= multiplier;

	return *this;
}

Vector3& Vector3::operator/=(float dividend)
{
	this->x_ /= dividend;
	this->y_ /= dividend;
	this->z_ /= dividend;

	return *this;
}

Vector3 Vector3::operator+(const Vector3& addend) const
{
	Vector3 sum = *this;
	sum += addend;

	return sum;
}

Vector3 Vector3::operator-(const Vector3& subtrahend) const
{
	Vector3 difference = *this;
	difference -= subtrahend;

	return difference;
}

Vector3 Vector3::operator*(float multiplier) const
{
	Vector3 product = *this;
	product *= multiplier;

	return product;
}

Vector3 Vector3::operator/(float dividend) const
{
	Vector3 quotient = *this;
	quotient /= dividend;

	return quotient;
}

void Vector3::Zero()
{
	this->x_ = 0.0f;
	this->y_ = 0.0f;
	this->z_ = 0.0f;
}
float Vector3::MagnitudeToOrigin() const
{
	return sqrtf(this->x_ * this->x_ + this->y_ * this->y_ + this->z_ * this->z_);
}