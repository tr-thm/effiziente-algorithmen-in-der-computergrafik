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
 * 
 * ------------------------------------------------------------------------------
 * Parts of the code is from SharpDX project. https://github.com/sharpdx/SharpDX
 * Original code published with the following license:
 * ------------------------------------------------------------------------------
 * 
 * Copyright (c) 2010-2014 SharpDX - Alexandre Mutel
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.

*/

#include <cmath>
#include "quaternion.h"

Quaternion::Quaternion()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 1;
};

Quaternion::Quaternion(float yaw, float pitch, float roll)
{
    float halfRoll = roll * 0.5f;
    float halfPitch = pitch * 0.5f;
    float halfYaw = yaw * 0.5f;

    float sinRoll = sinf(halfRoll);
    float cosRoll = cosf(halfRoll);
    float sinPitch = sinf(halfPitch);
    float cosPitch = cosf(halfPitch);
    float sinYaw = sinf(halfYaw);
    float cosYaw = cosf(halfYaw);

    this->x = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll);
    this->y = (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll);
    this->z = (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll);
    this->w = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll);
}

Quaternion::Quaternion(Vector3 axis, float angle)
{
    float half = angle * 0.5f;
    float sin = sinf(half);
    float cos = cosf(half);

    this->x = axis.x * sin;
    this->y = axis.y * sin;
    this->z = axis.z * sin;
    this->w = cos;
}

Quaternion Quaternion::rotation(Vector3 angles)
{
    return Quaternion(Vector3(0,0,1), angles.z) * Quaternion(Vector3(0,1,0), angles.y) * Quaternion(Vector3(1,0,0), angles.x);
}

Matrix Quaternion::toMatrix()
{
    Matrix m;
    // |1-2y²-2z²        2xy-2zw         2xz+2yw       0|
    // | 2xy+2zw        1-2x²-2z²        2yz-2xw       0|
    // | 2xz-2yw         2yz+2xw        1-2x²-2y²      0|
    // |    0               0               0          1|
    
    //row 1
    m.m11 = 1 - 2 * (this->y * this->y + this->z * this->z);
    m.m21 =     2 * (this->x * this->y - this->z * this->w);
    m.m31 =     2 * (this->x * this->z + this->y * this->w);
    m.m41 =     0;
    
    //row 2
    m.m12 =     2 * (this->x * this->y + this->z * this->w);
    m.m22 = 1 - 2 * (this->x * this->x + this->z * this->z);
    m.m32 =     2 * (this->y * this->z - this->x * this->w);
    m.m42 =     0;

    //row 3
    m.m13 =     2 * (this->x * this->z - this->y * this->w);
    m.m23 =     2 * (this->y * this->z + this->x * this->w);
    m.m33 = 1 - 2 * (this->x * this->x + this->y * this->y);
    m.m43 =     0;

    //row 4
    m.m14 =     0;
    m.m24 =     0;
    m.m34 =     0;
    m.m44 =     1;

    return m;
}

/**
 * Invert Quaternion
*/
Quaternion operator- (Quaternion q)
{
    Quaternion q2 = {};
    float lengthSq = (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);
    if (lengthSq > 0.0001)
    {
        lengthSq = 1.0f / lengthSq;

        q2.x = -q.x * lengthSq;
        q2.y = -q.y * lengthSq;
        q2.z = -q.z * lengthSq;
        q2.w = q.w * lengthSq;
    }
    return q2;
}

Quaternion operator* (Quaternion left, Quaternion right)
{
    float lx = left.x;
    float ly = left.y;
    float lz = left.z;
    float lw = left.w;
    float rx = right.x;
    float ry = right.y;
    float rz = right.z;
    float rw = right.w;
    float a = (ly * rz - lz * ry);
    float b = (lz * rx - lx * rz);
    float c = (lx * ry - ly * rx);
    float d = (lx * rx + ly * ry + lz * rz);
    Quaternion result;
    result.x = (lx * rw + rx * lw) + a;
    result.y = (ly * rw + ry * lw) + b;
    result.z = (lz * rw + rz * lw) + c;
    result.w = lw * rw - d;
    return result;
}

Vector3 operator* (Quaternion rotation, Vector3 vector)
{
    float x = rotation.x + rotation.x;
    float y = rotation.y + rotation.y;
    float z = rotation.z + rotation.z;
    float wx = rotation.w * x;
    float wy = rotation.w * y;
    float wz = rotation.w * z;
    float xx = rotation.x * x;
    float xy = rotation.x * y;
    float xz = rotation.x * z;
    float yy = rotation.y * y;
    float yz = rotation.y * z;
    float zz = rotation.z * z;

    Vector3 result;
    result.x = ((vector.x * ((1.0f - yy) - zz)) + (vector.y * (xy - wz))) + (vector.z * (xz + wy));
    result.y = ((vector.x * (xy + wz)) + (vector.y * ((1.0f - xx) - zz))) + (vector.z * (yz - wx));
    result.z = ((vector.x * (xz - wy)) + (vector.y * (yz + wx))) + (vector.z * ((1.0f - xx) - yy));
    return result;
}

Matrix operator* (Quaternion rotation, Matrix matrix)
{
    return rotation.toMatrix() * matrix;
}

Matrix operator* (Matrix matrix, Quaternion rotation)
{
    return matrix * rotation.toMatrix();
}
