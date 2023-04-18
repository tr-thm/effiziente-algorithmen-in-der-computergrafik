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

#include "texture.h"
#include "math/matrix.h"
#include "math/vector3.h"

class Shader
{
    public:
    Shader(std::string vertexShaderFile, std::string fragmentShaderFile);
    ~Shader();
    void activate();
    void setMatrix(int location, Matrix m);
    void setVector3(int location, Vector3 v);
    void setTexture(int location, Texture *texture);
    struct {
        int WorldMatrix;
        int ViewMatrix;
        int ProjectionMatrix;
        int SunLight;
        int CameraPos;
        int Diffuse;
        int NormalMap;
        int Roughness;
    } vars;

    private:
    unsigned int shaderProgram;
    bool shaderCompile(std::string filename, unsigned int *shader, unsigned int type);
    char *readFile(std::string filename);
};
