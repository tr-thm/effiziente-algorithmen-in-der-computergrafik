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
#include <iostream>
#include "collider.h"

Collider::Collider(float radius)
{
    this->type = ColliderType::sphere;
    this->radius = radius;
}

Collider::Collider(std::string filename)
{
    this->type = ColliderType::mesh;

    // TODO: load vertices from file

    // TODO: determine radius from vertices

    // TODO: store vertices or faces in an appropriate data structure
}

void Collider::update(Vector3 entityPosition, Quaternion entityRotation, Vector3 entityScale)
{
    // Update center and bounds for any collider type
    this->center = entityPosition;
    this->minimum = Vector3(
        entityPosition.x - radius,
        entityPosition.y - radius,
        entityPosition.z - radius
    );
    this->maximum = Vector3(
        entityPosition.x + radius,
        entityPosition.y + radius,
        entityPosition.z + radius
    );

    if (type == ColliderType::mesh)
    {
        // TODO: Store required transform data for mesh colliders        
    }
}

bool Collider::collidesWith(Collider *other, bool exact)
{
    // Broad phase: Terminate early if bounding boxes do not overlap
    if (this->maximum.x < other->minimum.x || other->maximum.x < this->minimum.x) return false;
    if (this->maximum.y < other->minimum.y || other->maximum.y < this->minimum.y) return false;
    if (this->maximum.z < other->minimum.z || other->maximum.z < this->minimum.z) return false;

    if (exact)
    {
        // Narrow phase: Perform exact collision detection
        if (this->type == ColliderType::sphere && other->type == ColliderType::sphere)
        {
            return (this->center - other->center).length() < this->radius + other->radius;
        }

        // TODO: Implement exact collision detection for other collider types
    }

    return true;
}
