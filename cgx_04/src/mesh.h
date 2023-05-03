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
#include <map>
#include <string>
#include <vector>

#include "math/vertex.h"

class Mesh
{
    public:
        Mesh(std::string);
        ~Mesh();
        void draw();
        static Mesh* acquire(std::string filename);
        static void release(Mesh *mesh);

    private:
        std::string filename;
        unsigned int vertexAttributes = 0, vertexBuffer = 0;
        std::vector<Vertex> *vertices = nullptr;
        unsigned int vertexCount = 0;
        unsigned int usageCount = 0;
        void init();
        static inline std::map<std::string, Mesh*> cache;
};
