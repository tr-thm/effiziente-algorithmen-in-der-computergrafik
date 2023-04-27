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
#include <chrono>
#include <iostream>
#include <map>
#include <string>

#include <GLFW/glfw3.h>

class Timer
{
    public:
    Timer(std::string name)
    {
        this->name = name;
        this->start = std::chrono::steady_clock::now();
    }
    void stop()
    {
        double now = glfwGetTime();
        std::cout << "Timer: " << this->name << " = " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->start).count() << " ms. Elapsed = " << now << " s." << std::endl;
    }

    private:
    std::string name;
    std::chrono::steady_clock::time_point start;
};
