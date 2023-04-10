#include <cmath>

#include "vector3.h"

Vector3::Vector3()
{
    this->x = this->y = this->z = 0;
}

Vector3::Vector3(float x, float y, float z)
{ 
    this->x = x;
    this->y = y;
    this->z = z;
};

Vector3 Vector3::FromDegrees(float x, float y, float z)
{
    Vector3 v;
    v.x = x * M_PI / 180.0f;
    v.y = y * M_PI / 180.0f;
    v.z = z * M_PI / 180.0f;
    return v;
}

Vector3 operator* (const Vector3& v, float f)
{
    return (Vector3){v.x * f, v.y * f, v.z * f};
}

Vector3 operator+ (const Vector3& a, const Vector3& b)
{
    return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 operator- (const Vector3& a, const Vector3& b)
{
    return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector3 operator- (const Vector3& a)
{
    return Vector3(-a.x, -a.y, -a.z);
}
