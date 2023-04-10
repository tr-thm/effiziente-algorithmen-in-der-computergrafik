#pragma once
#include <string>
#include "math/vector3.h"

typedef void (*LogicFunction)(Vector3&, Vector3&, const double);

static void earthRotation(Vector3 &position, Vector3 &rotation, const double time)
{
    rotation.y += 0.0001f;
}

static LogicFunction logicGetFunction(std::string name)
{
    if ("earthRotation" == name) return earthRotation;
    return nullptr;
}
