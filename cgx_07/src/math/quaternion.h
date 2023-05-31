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
#include "matrix.h"

struct Quaternion
{
    float x, y, z, w;
    
    Quaternion();
    Quaternion(float yaw, float pitch, float roll);
    Quaternion(Vector3 axis, float angle);

    Matrix toMatrix();
    static Quaternion rotation(Vector3 angles);
};

Quaternion operator* (Quaternion left, Quaternion right);
Vector3 operator* (Quaternion rotation, Vector3 vector);
Matrix operator* (Quaternion rotation, Matrix matrix);
Matrix operator* (Matrix matrix, Quaternion rotation);
Quaternion operator- (Quaternion q);