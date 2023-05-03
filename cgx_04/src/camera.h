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

#include "math/matrix.h"
#include "math/quaternion.h"
#include "math/vector2.h"
#include "math/vector3.h"

class Camera
{
    public:
        Camera(std::string name);
        void setType(std::string type);
        void setPosition(Vector3 position);
        void setRotation(Vector3 rotation);
        bool isOrbiting();
        void update(Vector3 &entityPosition, Quaternion &entityRotation, const double time);
        std::string getName();
        std::string getType();
        void move(float, float, float, float);

        static Vector3 getPosition();
        static Matrix getProjectionMatrix();
        static Matrix getViewMatrix(bool fixed);
        static void setAspectRatio(float aspect);
        static void handleInput(float, float, float, float);

    private:
        std::string name;
        std::string type;
        Vector3 position;
        Vector3 rotation;

        static inline Camera *activeCamera = nullptr;
        static inline Matrix projectionMatrix = Matrix();
        static inline Matrix viewMatrix = Matrix();
        static inline Matrix fixedViewMatrix = Matrix();
        static inline Vector3 absolutePosition = Vector3();
};