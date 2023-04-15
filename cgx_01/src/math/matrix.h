/**
 * Effiziente Algorithmen in der Computergrafik
 * Copyright (C) 2023 Tobias Reimann
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
    static Matrix rotationInv(const Vector3 &rotation);
    static Matrix rotation(const Vector3 &rotation);
    static Matrix rotationX(float a);
    static Matrix rotationY(float a);
    static Matrix rotationZ(float a);
    static Matrix scale(const Vector3 &scale);
    static Matrix translation(const Vector3 &position);
    static Matrix perspective(double fov, double aspect, double zNear, double zFar);
};

Matrix operator* (const Matrix &a, const Matrix &b);
Matrix operator- (const Matrix &a);
Vector3 operator* (const Matrix &m, const Vector3 &v);