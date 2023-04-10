#include "vertex.h"

Vertex::Vertex(const Vector3& pos, const Vector2& texcoord, const Vector3& normal)
{
    this->pos = pos;
    this->texcoord = texcoord;
    this->normal = normal;
}
