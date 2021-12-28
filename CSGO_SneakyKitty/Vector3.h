#pragma once

class Vector3
{
public:

    float x_;
    float y_;
    float z_;

    Vector3() = default;
    Vector3(float new_x, float new_y, float new_z);

    Vector3& operator+=(const Vector3& addend);
    Vector3& operator-=(const Vector3& subtrahend);
    Vector3& operator*=(float multiplier);
    Vector3& operator/=(float dividend);

    Vector3 operator+ (const Vector3& addend) const;
    Vector3 operator- (const Vector3& subtrahend) const;
    Vector3 operator* (float multiplier) const;
    Vector3 operator/(float dividend) const;


    void Zero();
    float MagnitudeToOrigin() const;
};

