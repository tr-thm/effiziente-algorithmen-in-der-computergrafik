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
#include <vector>

#include "scene.h"
#include "settings.h"
#include "math/vector3.h"

class Game
{
    public:
        static void setKey(int key, int state);
        static bool getKey(int key);
        static void setMouse(double dx, double dy, double sx, double sy);
        static void load(Settings settings);
        static void loop(const double &time);
        static void unload();

    private:
        static inline bool gameKeyState[384] = {};
        static inline Vector3 cameraPosition = Vector3(7.3589, -6.9258, 4.9583);
        static inline Vector3 cameraRotation = Vector3::FromDegrees(63.6,  0.0, 46.7);
        static inline double walkSpeed = 3.0;
        static inline double mouseSpeed = 0.001;
        static inline Scene *scene = nullptr;
};
