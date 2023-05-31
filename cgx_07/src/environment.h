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

#include <GLFW/glfw3.h>

#include "math/vector3.h"
#include "skybox.h"

struct Environment
{
    Vector3 background = Vector3(0,0,0);
    Vector3 sunDirection = Vector3(0,0,-1);
    std::string sky;
    Skybox *skybox = nullptr;

    void load()
    {
        glClearColor(background.x, background.y, background.z, 1.0);
        if (!sky.empty())
        {
            skybox = new Skybox(sky);
        }
    }

    void render()
    {
        if (skybox != nullptr) skybox->render();
    }
    
    void unload()
    {
        delete skybox;
        skybox = nullptr;
    }
};