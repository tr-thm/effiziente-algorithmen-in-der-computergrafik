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
#include <functional>

#include "vector2.h"
#include "vector3.h"

struct Vertex
{
    Vector3 pos;
    Vector2 texcoord;
    Vector3 normal;
    Vector3 tangent;

    Vertex(const Vector3 &pos, const Vector2 &texcoord, const Vector3 &normal);

    static void computeTangents(Vertex &v1, Vertex &v2, Vertex &v3);
    
    friend bool operator== (const Vertex &left, const Vertex &right);
};

struct VertexHashFunction
{
    size_t operator()(const Vertex &v) const;
};