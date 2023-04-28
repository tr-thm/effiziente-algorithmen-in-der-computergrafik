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

#include "camera.h"
#include "filereader.h"
#include "graphics.h"
#include "scene.h"
#include "math/vector3.h"

Scene::Scene(std::string filename)
{
    FileReader reader = FileReader(filename);
    bool active;
    Environment env = Environment();
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "env")
        {
            std::string key = reader.getString();
            if (key == "background")
            {
                env.background = reader.getVector3();
            }
            else if (key == "sun")
            {
                env.sun = reader.getVector3();
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
            entities[entities.size() - 1]->setRotation(Vector3::FromDegrees(x, y, z));
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
    }
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->load();
    }
    Graphics::setEnvironment(env);
    switchEntity();
}

Scene::~Scene()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
    entities.clear();
}

void Scene::update(const double time)
{
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(time);
    }
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
