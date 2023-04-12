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

#include "entity.h"
#include "graphics.h"
#include "logic.h"

Entity::Entity(std::string name)
{
    this->name = name;
}

void Entity::setModel(std::string model)
{
    this->model = model;
}
void Entity::setPosition(Vector3 position)
{
    this->position = position;
}
void Entity::setRotation(Vector3 rotation)
{
    this->rotation = rotation;
}
void Entity::setScale(Vector3 scale)
{
    this->scale = scale;
}

void Entity::addFlag(std::string flag)
{
    this->flags.push_back(flag);
}

void Entity::addLogic(std::string logic)
{
    LogicFunction lf = logicGetFunction(logic);

    if (lf != nullptr) this->logic.push_back(lf);
}

void Entity::load()
{
    this->modelId = Graphics::loadModel(this->model);
    for (int i = 0; i < this->flags.size(); i++)
    {
        Graphics::updateModel(this->modelId, this->flags[i]);
    }
}

void Entity::update(const double time)
{
    for (int i = 0; i < logic.size(); i++)
    {
        logic[i](position, rotation, time);
    }

    Graphics::updateModel(this->modelId, position, rotation, scale);
}

Entity::~Entity()
{
    Graphics::unloadModel(this->modelId);
}