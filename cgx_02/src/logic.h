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
#include <string>
#include "math/vector3.h"

typedef void (*LogicFunction)(Vector3 &position, Vector3 &rotation, const double time);

static void earthRotation(Vector3 &position, Vector3 &rotation, const double time)
{
    rotation.y += 0.0001f;
}

static LogicFunction logicGetFunction(std::string name)
{
    if ("earthRotation" == name) return earthRotation;
    return nullptr;
}
