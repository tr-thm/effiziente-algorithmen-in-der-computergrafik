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
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "math/vector2.h"
#include "math/vector3.h"

class FileReader
{
    public:
        FileReader(std::string filename);
        bool hasLine();
        std::string getString();
        float getFloat();
        Vector2 getVector2();
        Vector3 getVector3();
        std::vector<int> getVertex();

    private:
        std::string filename;
        int line = 0;
        std::ifstream fileStream;
        std::istringstream lineStream;
};
