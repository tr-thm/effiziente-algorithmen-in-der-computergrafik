#pragma once

struct Vector3
{
    float x, y, z;
    Vector3();
    Vector3(float x, float y, float z);
    
    static Vector3 FromDegrees(float x, float y, float z);
};

Vector3 operator* (const Vector3& v, float f);
Vector3 operator+ (const Vector3& a, const Vector3& b);
Vector3 operator- (const Vector3& a, const Vector3& b);
Vector3 operator- (const Vector3& a);
