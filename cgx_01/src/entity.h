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
#include <vector>

#include "logic.h"
#include "math/vector3.h"

class Entity
{
    public:
    Entity(std::string name);
    ~Entity();
    void setModel(std::string model);
    void setPosition(Vector3 position);
    void setRotation(Vector3 rotation);
    void setScale(Vector3 scale);
    void addFlag(std::string flag);
    void addLogic(std::string logic);
    void load();
    void update(double time);

    private:
    int modelId;
    std::string name;
    std::string model;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale = Vector3(1,1,1);
    std::vector<std::string> flags;
    std::vector<LogicFunction> logic;
};
