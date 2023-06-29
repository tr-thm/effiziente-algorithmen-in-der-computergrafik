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

struct Vector3
{
    float x, y, z;
    Vector3();
    Vector3(float x, float y, float z);

    float length();
    void normalize();
    
    static Vector3 FromDegrees(float x, float y, float z);
    static float distance(const Vector3 &a, const Vector3 &b);
    static float dot(const Vector3 &a, const Vector3 &b);
    static Vector3 closestPointOnLine(const Vector3 &startPos, const Vector3 &endPos, const Vector3 &point);
};

Vector3 operator* (const Vector3 &v, float f);
Vector3 operator* (const Vector3 &a, const Vector3 &b);
Vector3 operator+ (const Vector3 &a, const Vector3 &b);
Vector3 operator- (const Vector3 &a, const Vector3 &b);
Vector3 operator- (const Vector3 &a);
bool operator== (const Vector3 &a, const Vector3 &b);
