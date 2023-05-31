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

void Vertex::computeTangents(Vertex &v1, Vertex &v2, Vertex &v3)
{
    Vector3 edge1 = v2.pos - v1.pos;
    Vector3 edge2 = v3.pos - v1.pos;

    Vector2 deltaUV1 = v2.texcoord - v1.texcoord;
    Vector2 deltaUV2 = v3.texcoord - v1.texcoord;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    Vector3 tangent = Vector3(
        f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
        f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
        f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)
    );
    tangent.normalize();
    
    v1.tangent = v1.tangent + tangent;
    v2.tangent = v2.tangent + tangent;
    v3.tangent = v3.tangent + tangent;
}

bool operator== (const Vertex &left, const Vertex &right)
{
    return left.pos == right.pos
        && left.texcoord == right.texcoord
        && left.normal == right.normal
        && left.tangent == right.tangent;
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
    size_t txHash = std::hash<float>()(v.tangent.x) << 8;
    size_t tyHash = std::hash<float>()(v.tangent.y) << 9;
    size_t tzHash = std::hash<float>()(v.tangent.z) << 10;
    return xHash ^ yHash ^ zHash
         ^ uHash ^ vHash
         ^ nxHash ^ nyHash ^ nzHash
         ^ txHash ^ tyHash ^ tzHash;
}