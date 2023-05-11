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

#include "logic.h"
#include "game.h"

void Logic::earthRotation(Vector3 &position, Vector3 &speed, Quaternion &rotation, Vector3 &angularVelocity, const double time)
{
    Vector3 av = Vector3(0, 0, 0.005) * time;
    rotation = rotation * Quaternion::rotation(av);
}

void Logic::shipControl(Vector3 &position, Vector3 &speed, Quaternion &rotation, Vector3 &angularVelocity, const double time)
{
    //Define acceleration of the ship
    //Remember: a = F / m
    float a = 1;
    Vector3 acceleration = Vector3();
    if (Game::getKey(87))  acceleration.x += a;
    if (Game::getKey(83))  acceleration.x -= a;
    if (Game::getKey(65))  acceleration.y += a;
    if (Game::getKey(68))  acceleration.y -= a;
    if (Game::getKey(32))  acceleration.z += a;
    if (Game::getKey(341)) acceleration.z -= a;

    //Define angular acceleration of the ship
    //Remeber: aa = T / I
    float aa = 1;
    Vector3 angularAcceleration = Vector3();
    if (Game::getKey(76))  angularAcceleration.x += aa;
    if (Game::getKey(74))  angularAcceleration.x -= aa;
    if (Game::getKey(73))  angularAcceleration.y += aa;
    if (Game::getKey(75))  angularAcceleration.y -= aa;
    if (Game::getKey(85))  angularAcceleration.z += aa;
    if (Game::getKey(79))  angularAcceleration.z -= aa;

    //Apply changes to speed and angular velocity of the ship
    //Remember: v = a * t      av = aa * t
    speed = speed + rotation * acceleration * time;
    angularVelocity = angularVelocity + angularAcceleration * time;
}

void Logic::physics(Vector3 &position, Vector3 &speed, Quaternion &rotation, Vector3 &angularVelocity, const double time)
{
    position = position + speed * time;
    rotation = rotation * Quaternion::rotation(angularVelocity * time);
}

LogicFunction Logic::getFunction(std::string name)
{
    if ("earthRotation" == name) return earthRotation;
    if ("physics" == name) return physics;
    if ("shipControl" == name) return shipControl;
    return nullptr;
}
