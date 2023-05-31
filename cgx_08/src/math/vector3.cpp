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

Vector3 operator* (const Vector3 &v, float f)
{
    return (Vector3){v.x * f, v.y * f, v.z * f};
}

Vector3 operator+ (const Vector3 &a, const Vector3 &b)
{
    return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 operator- (const Vector3 &a, const Vector3 &b)
{
    return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector3 operator- (const Vector3 &a)
{
    return Vector3(-a.x, -a.y, -a.z);
}

bool operator== (const Vector3 &a, const Vector3 &b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

float Vector3::length()
{
    return (float)sqrt((x * x) + (y * y) + (z * z));
}

void Vector3::normalize()
{
    float length = this->length();
    if (length >= 1e-6f)
    {
        float inv = 1.0f / length;
        x *= inv;
        y *= inv;
        z *= inv;
    }
}
