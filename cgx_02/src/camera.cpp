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

#include <cmath>
#include <iostream>

#include "camera.h"

Camera::Camera(std::string name)
{
    this->name = name;
}

void Camera::setType(std::string type)
{
    this->type = type;
}

void Camera::setPosition(Vector3 position)
{
    this->position = position;
}

void Camera::setRotation(Vector3 rotation)
{
    this->rotation = rotation;
}

void Camera::setLimits(Vector2 yawLimit, Vector2 pitchLimit, Vector2 distLimit)
{
    this->yawLimit = yawLimit;
    this->pitchLimit = pitchLimit;
    this->distLimit = distLimit;
}

std::string Camera::getName()
{
    return name;
}

std::string Camera::getType()
{
    return type;
}

void Camera::update(Vector3 &entityPosition, Vector3 &entityRotation, const double time)
{
    activeCamera = this;

    Matrix entityRotationMatrix = -Matrix::rotation(entityRotation);
    Matrix entityPositionMatrix = -Matrix::translation(entityPosition);

    Matrix cameraRotationMatrix;
    Matrix cameraPositionMatrix;

    if (this->type == "fixed")
    {
        cameraRotationMatrix = -Matrix::rotation(this->rotation);
        cameraPositionMatrix = -Matrix::translation(position);
        absolutePosition = entityPosition + Matrix::rotation(entityRotation) * position;
    }
    else if (this->type == "orbit")
    {
        cameraRotationMatrix = Matrix::rotation(Vector3::FromDegrees(90, 0, 90));
        Matrix cameraYawMatrix = Matrix::rotationY(this->rotation.x);
        Matrix cameraPitchMatrix = Matrix::rotationX(this->rotation.y);

        Vector3 anchor = Vector3(0, 0, this->rotation.z);
        anchor = cameraRotationMatrix * cameraYawMatrix * cameraPitchMatrix * anchor;

        cameraRotationMatrix = -cameraPitchMatrix * -cameraYawMatrix * -cameraRotationMatrix;
        cameraPositionMatrix = -Matrix::translation(anchor) * -Matrix::translation(position);

        absolutePosition = entityPosition + Matrix::rotation(entityRotation) * anchor;

        //std::cout << "Abs Pos " << absolutePosition.x << ":" << absolutePosition.y << ":" << absolutePosition.z << std::endl; 
    }

    viewMatrix = cameraRotationMatrix * cameraPositionMatrix * entityRotationMatrix * entityPositionMatrix;
    fixedViewMatrix = cameraRotationMatrix * entityRotationMatrix;
}

void Camera::move(float dx, float dy, float sx, float sy)
{
    if (this->type == "orbit")
    {
        this->rotation.x -= dx;
        this->rotation.y -= dy;
        this->rotation.z -= sy;

        if (this->rotation.y < -M_PI_2) this->rotation.y = -M_PI_2;
        if (this->rotation.y > M_PI_2) this->rotation.y = M_PI_2;

        if (this->rotation.z < 6) this->rotation.z = 6;
    }
}

bool Camera::isOrbiting()
{
    return this->type == "orbiting";
}

/* - - - - */

Vector3 Camera::getPosition()
{
    return absolutePosition;
}

Matrix Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

Matrix Camera::getViewMatrix(bool fixed)
{
    if (fixed) return fixedViewMatrix;
    return viewMatrix;
}

void Camera::setAspectRatio(float aspect)
{
    double zNear = 0.1;
    double zFar = 10000.0;
    double fov = 0.785; //45deg

    projectionMatrix = Matrix::perspective(fov, aspect, zNear, zFar);
}

void Camera::handleInput(float dx, float dy, float sx, float sy)
{
    if (activeCamera != nullptr)
    {
        activeCamera->move(dx, dy, sx, sy);
    }
}