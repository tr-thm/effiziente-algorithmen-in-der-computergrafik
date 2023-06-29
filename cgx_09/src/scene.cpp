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
#include <chrono>

#include "camera.h"
#include "filereader.h"
#include "graphics.h"
#include "scene.h"
#include "math/vector3.h"

Scene::Scene(std::string filename)
{
    FileReader reader = FileReader(filename);
    bool active;
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "env")
        {
            std::string key = reader.getString();
            if (key == "background")
            {
                Graphics::setBackground(reader.getVector3());
            }
            else if (key == "sun")
            {
                Graphics::setSun(reader.getVector3());
            }
            else if (key == "sky")
            {
                Graphics::setSky(reader.getString());
            }
        }
        else if (type == "e")
        {
            entities.push_back(new Entity(reader.getString()));
            active = false;
        }
        else if (type == "m")
        {
            entities[entities.size() - 1]->setModel(reader.getString());
        }
        else if (type == "p")
        {
            entities[entities.size() - 1]->setPosition(reader.getVector3());
        }
        else if (type == "r")
        {
            float x = reader.getFloat();
            float y = reader.getFloat();
            float z = reader.getFloat();
            entities[entities.size() - 1]->setRotation(Quaternion::rotation(Vector3::FromDegrees(x, y, z)));
        }
        else if (type == "s")
        {
            entities[entities.size() - 1]->setScale(reader.getVector3());
        }
        else if (type == "f")
        {
            entities[entities.size() - 1]->addFlag(reader.getString());
        }
        else if (type == "l")
        {
            entities[entities.size() - 1]->addLogic(reader.getString());
        }
        else if (type == "c")
        {
            Camera c = Camera(reader.getString());
            std::string ctype = reader.getString();
            c.setType(ctype);
            c.setPosition(reader.getVector3());
            if (ctype == "fixed")
            {
                float x = reader.getFloat();
                float y = reader.getFloat();
                float z = reader.getFloat();
                c.setRotation(Vector3::FromDegrees(x, y, z));
            }
            else if (ctype == "orbit")
            {
                float x = reader.getFloat();
                float y = reader.getFloat();
                Vector3 rotation = Vector3::FromDegrees(x, y, 0);
                rotation.z = reader.getFloat();
                c.setRotation(rotation);
            }
            entities[entities.size() - 1]->addCamera(c);
            if (!active)
            {
                activeEntities.push_back(entities[entities.size() - 1]);
                active = true;
            }
        }
        else if (type == "collider")
        {
            std::string colliderType = reader.getString();
            if (colliderType == "sphere")
            {
                float radius = reader.getFloat();
                entities[entities.size() - 1]->setCollider(new Collider(radius));
                collidableEntities.push_back(entities[entities.size() - 1]);
                sortedCollidableEntities[0].push_back(entities[entities.size() - 1]);
                sortedCollidableEntities[1].push_back(entities[entities.size() - 1]);
                sortedCollidableEntities[2].push_back(entities[entities.size() - 1]);
            }
            else if (colliderType == "mesh")
            {
                std::string filename = reader.getString();
                entities[entities.size() - 1]->setCollider(new Collider(filename));
                collidableEntities.push_back(entities[entities.size() - 1]);
                sortedCollidableEntities[0].push_back(entities[entities.size() - 1]);
                sortedCollidableEntities[1].push_back(entities[entities.size() - 1]);
                sortedCollidableEntities[2].push_back(entities[entities.size() - 1]);
            }
        }
    }
    Graphics::loadEnvironment();
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->load();
    }
    switchEntity();
}

Scene::~Scene()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
    entities.clear();
    activeEntities.clear();
    collidableEntities.clear();
    sortedCollidableEntities[0].clear();
    sortedCollidableEntities[1].clear();
    sortedCollidableEntities[2].clear();
}

void Scene::update(const double time)
{
    //update all entities
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(time);
    }
    std::cout << "update: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;

    // detect collisions the easy way
    start = std::chrono::steady_clock::now();
    std::vector<std::pair<Entity*,Entity*>> collisions = determineCollisions();
    std::cout << "detect: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
    
    // detect collisions the better way
    start = std::chrono::steady_clock::now();
    std::vector<std::pair<Entity*,Entity*>> collisions2 = sortAndSweep();
    std::cout << "sweep:  " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
    
    resolveCollisions(collisions2, time);
}

void Scene::switchEntity()
{
    if (activeEntities.size() > 0)
    {
        activeEntity = (activeEntity + 1) % activeEntities.size();
        for (int i = 0; i < activeEntities.size(); i++)
        {
            activeEntities[i]->setFocus(activeEntity == i);
        }
    }
}

void Scene::switchCamera()
{
    if (activeEntity >= 0)
    {
        activeEntities[activeEntity]->switchCamera();
    }
}

void Scene::sortEntities(std::vector<Entity*> &A)
{
    int i = 1;
    int length = A.size();
    while (i < length)
    {
        Entity *x = A[i];
        int j = i - 1;
        while (j >= 0 && compareEntities(A[j], x))
        {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = x;
        i = i + 1;
    }
}

bool Scene::compareEntities(Entity *a, Entity *b)
{
    if (selectedSortedAxis == 0)
    {
        return a->collider->minimum.x > b->collider->minimum.x;
    }
    else if (selectedSortedAxis == 1)
    {
        return a->collider->minimum.y > b->collider->minimum.y;
    }
    else
    {
        return a->collider->minimum.z > b->collider->minimum.z;
    }
}

std::vector<std::pair<Entity*,Entity*>> Scene::sortAndSweep()
{
    std::vector<std::pair<Entity*,Entity*>> collisions;

    std::vector<Entity*> entities = sortedCollidableEntities[selectedSortedAxis];

    sortEntities(entities);

    int size = entities.size();
    for (int i = 0; i < size; i++)
    {
        Entity *e1 = entities[i];
        for (int j = i + 1; j < size; j++)
        {
            Entity *e2 = entities[j];
            if (selectedSortedAxis == 0 && e1->collider->maximum.x < e2->collider->minimum.x)
            {
                break;
            }
            else if (selectedSortedAxis == 1 && e1->collider->maximum.y < e2->collider->minimum.y)
            {
                break;
            }
            else if (selectedSortedAxis == 2 && e1->collider->maximum.z < e2->collider->minimum.z)
            {
                break;
            }
            else if (e1->collidesWith(e2, true))
            {
                collisions.push_back(std::pair<Entity*,Entity*>(e1, e2));
            }
        }
    }
    return collisions;
}

std::vector<std::pair<Entity*,Entity*>> Scene::determineCollisions()
{
    std::vector<std::pair<Entity*,Entity*>> collisions;
    int size = collidableEntities.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (collidableEntities[i]->collidesWith(collidableEntities[j], true))
            {
                collisions.push_back(std::pair<Entity*,Entity*>(collidableEntities[i], collidableEntities[j]));
            }
        }
    }
    return collisions;
}

void Scene::resolveCollisions(std::vector<std::pair<Entity*,Entity*>> &collisions, const double time)
{
    for (auto collision : collisions)
    {
        //implement collision response assuming an elastic collision, both entities weigh the same
        Entity *entity1 = collision.first;
        Entity *entity2 = collision.second;

        //move both entities back to the beginning of the frame
        entity1->position = entity1->position - entity1->speed * time;
        entity2->position = entity2->position - entity2->speed * time;

        //calculate the normal of the collision plane
        Vector3 normal = entity1->position - entity2->position;
        normal.normalize();

        //calculate the relative speed of the entities
        Vector3 relativeSpeed = entity1->speed - entity2->speed;

        //calculate the impulse
        float impulse = Vector3::dot(relativeSpeed, normal);

        //calculate the new speed of the entities
        entity1->speed = entity1->speed - normal * impulse;
        entity2->speed = entity2->speed + normal * impulse;

        //move both entities forward to the end of the frame
        entity1->position = entity1->position + entity1->speed * time;
        entity2->position = entity2->position + entity2->speed * time;

    }

}
