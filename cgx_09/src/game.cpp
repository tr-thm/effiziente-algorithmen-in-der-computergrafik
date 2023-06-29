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
#include <vector>

#include "camera.h"
#include "game.h"
#include "scene.h"
#include "settings.h"
#include "math/matrix.h"
#include "math/quaternion.h"
#include "math/vector3.h"

void Game::setKey(int key, int state)
{
    //A=65; S=83; D=68; W=87; SPACE=32; LSHIFT=340; LCTRL=341; Q=81; E=69;
    //J=74; K=75; L=76; U=85; O=79
    gameKeyState[key] = state > 0;
    std::cout << "key:" << key << "; state=" << state << std::endl;

    if (key == 258 && state == 1)  // TAB
    {
        scene->switchEntity();
    }
    else if (key == 67 && state == 1)  // C
    {
        scene->switchCamera();
    }
}

bool Game::getKey(int key)
{
    return gameKeyState[key];
}

void Game::setMouse(double dx, double dy, double sx, double sy)
{
    Camera::handleInput(dx * mouseSpeed, dy * mouseSpeed, sx * scrollSpeed, sy * scrollSpeed);
}

void Game::load(Settings settings)
{
    mouseSpeed *= settings.mouseSpeed;

    std::cout << "Loading splash screen..." << std::endl;
    scene = new Scene("scenes/splash.scene");
}

void Game::loop(const double &time)
{
    if (scene != nullptr)
    {
        scene->update(time);
        if (splash < 31)
        {
            if (splash == 30)
            {
                std::cout << "Loading main scene..." << std::endl;
                delete scene;
                scene = new Scene("scenes/collisions.scene");
            }
            splash++;
        }
    }
}

void Game::unload()
{
    delete scene;
    scene = nullptr;
}
