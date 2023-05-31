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

#include "vertex.h"

Vertex::Vertex(const Vector3 &pos, const Vector2 &texcoord, const Vector3 &normal)
 : pos(pos), texcoord(texcoord), normal(normal) { }

bool operator== (const Vertex &left, const Vertex &right)
{
    return left.pos == right.pos
        && left.texcoord == right.texcoord
        && left.normal == right.normal;
}

size_t VertexHashFunction::operator() (const Vertex &v) const
{
    size_t xHash = std::hash<float>()(v.pos.x);
    size_t yHash = std::hash<float>()(v.pos.y) << 1;
    size_t zHash = std::hash<float>()(v.pos.z) << 2;
    size_t uHash = std::hash<float>()(v.texcoord.x) << 3;
    size_t vHash = std::hash<float>()(v.texcoord.y) << 4;
    size_t nxHash = std::hash<float>()(v.normal.x) << 5;
    size_t nyHash = std::hash<float>()(v.normal.y) << 6;
    size_t nzHash = std::hash<float>()(v.normal.z) << 7;
    return xHash ^ yHash ^ zHash
         ^ uHash ^ vHash
         ^ nxHash ^ nyHash ^ nzHash;
}