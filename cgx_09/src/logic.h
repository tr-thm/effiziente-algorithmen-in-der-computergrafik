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
#include "math/quaternion.h"
#include "math/vector3.h"

typedef void (*LogicFunction)(Vector3 &position, Vector3 &speed, Quaternion &rotation, Vector3 &angularVelocity, const double time);

class Logic
{
    public:
        static void earthRotation(Vector3 &position, Vector3 &speed, Quaternion &rotation, Vector3 &angularVelocity, const double time);
        static void shipControl(Vector3 &position, Vector3 &speed, Quaternion &rotation, Vector3 &angularVelocity, const double time);
        static void physics(Vector3 &position, Vector3 &speed, Quaternion &rotation, Vector3 &angularVelocity, const double time);
        static LogicFunction getFunction(std::string name);
};
