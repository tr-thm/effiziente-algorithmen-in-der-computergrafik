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

#include "cubemap.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "math/vector3.h"

class Model
{
    public:
        Model(std::string filename);
        ~Model();
        void setTransform(Matrix m);
        void toggleFlag(std::string flag);
        void render(Vector3 sunLight);
        bool skipDepthTesting();

    protected:
        Model() {};
        bool nodepth = false;
        bool fixed = false;
        Matrix worldMatrix;
        Shader *shader = nullptr;
        Mesh *mesh = nullptr;
        struct {
            Texture *Diffuse = nullptr;
            Texture *NormalMap = nullptr;
            Texture *Roughness = nullptr;
            CubeMap *Skybox = nullptr;
            Texture *AR = nullptr;
            Texture *NOM = nullptr;
            Texture *PMDG = nullptr;
        } textures;
};
