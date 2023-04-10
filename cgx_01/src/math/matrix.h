#pragma once
#include "vector3.h"

struct Matrix
{
    float m11;
    float m12;
    float m13;
    float m14;
    float m21;
    float m22;
    float m23;
    float m24;
    float m31;
    float m32;
    float m33;
    float m34;
    float m41;
    float m42;
    float m43;
    float m44;

    Matrix();
    static Matrix rotationInv(const Vector3& rotation);
    static Matrix rotation(const Vector3& rotation);
    static Matrix rotationX(float a);
    static Matrix rotationY(float a);
    static Matrix rotationZ(float a);
    static Matrix scale(const Vector3& scale);
    static Matrix translation(const Vector3& position);
    static Matrix perspective(double fov, double aspect, double zNear, double zFar);
};

Matrix operator* (const Matrix& a, const Matrix& b);
Matrix operator- (const Matrix& a);
Vector3 operator* (const Matrix& m, const Vector3& v);