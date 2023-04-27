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

#include "game.h"
#include "graphics.h"
#include "settings.h"
#include "window.h"

int main()
{
    std::cout << "Engine starting..." << std::endl;

    Settings settings;

    if (Window::create(settings) && Graphics::start(settings))
    {
        Game::load(settings);
        double dtime = 0;
        while (Window::loop(&dtime))
        {
            Game::loop(dtime);
            Graphics::loop();
        }
        Game::unload();
        Graphics::terminate();
        Window::destroy();
    }

    std::cout << "Engine terminated." << std::endl;

    return 0;
}