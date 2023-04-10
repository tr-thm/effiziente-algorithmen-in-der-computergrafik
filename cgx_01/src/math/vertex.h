#pragma once
#include "vector2.h"
#include "vector3.h"

struct Vertex
{
    Vector3 pos;
    Vector2 texcoord;
    Vector3 normal;

    Vertex(const Vector3& pos, const Vector2& texcoord, const Vector3& normal);
};
