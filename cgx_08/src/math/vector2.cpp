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

#include "vector2.h"

Vector2::Vector2()
{
    this->x = this->y = 0;
}

Vector2::Vector2(float x, float y)
{ 
    this->x = x;
    this->y = y;
};

Vector2 operator- (const Vector2 &a, const Vector2 &b)
{
    return Vector2(a.x - b.x, a.y - b.y);
}

bool operator== (const Vector2 &a, const Vector2 &b)
{
    return a.x == b.x && a.y == b.y;
}
