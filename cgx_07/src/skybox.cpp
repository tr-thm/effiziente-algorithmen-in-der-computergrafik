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

#include <cmath>

#include "camera.h"
#include "skybox.h"
#include "math/matrix.h"

Skybox::Skybox(std::string filename)
{
    this->mesh = Mesh::acquire("meshes/cubemap.obj");
    this->shader = Shader::acquire("shaders/vertex_shader_skybox.glsl", "shaders/fragment_shader_skybox.glsl");
    this->textures.Skybox = CubeMap::acquire(filename);
}

void Skybox::render()
{
    shader->activate();

    shader->setMatrix(shader->vars.ProjectionMatrix, Camera::getProjectionMatrix());
    shader->setMatrix(shader->vars.ViewMatrix, Camera::getViewMatrix(true));
    shader->setMatrix(shader->vars.WorldMatrix, worldMatrix);

    shader->setTexture(shader->vars.Skybox, textures.Skybox);
    
    mesh->draw();
}