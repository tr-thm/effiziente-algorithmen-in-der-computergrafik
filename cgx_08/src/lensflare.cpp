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
#include "graphics.h"
#include "lensflare.h"
#include "math/matrix.h"

Lensflare::Lensflare()
{
    this->mesh = Mesh::acquire("meshes/screen.obj");
    this->shader = Shader::acquire("shaders/vertex_shader_lensflare.glsl", "shaders/fragment_shader_lensflare.glsl");
    this->textures.Diffuse = Texture::acquire("textures/rgb-noise.dds");
    this->worldMatrix = Matrix::translation(Vector3(-10.0, 10.0, 5.0));
}

void Lensflare::render(Vector3 sunLight, float sunVisibility)
{
    shader->activate();

    shader->setMatrix(shader->vars.ProjectionMatrix, Camera::getProjectionMatrix());
    shader->setMatrix(shader->vars.ViewMatrix, Camera::getViewMatrix(true));
    shader->setMatrix(shader->vars.WorldMatrix, worldMatrix);
    
    shader->setVector3(shader->vars.ViewportSize, Graphics::getViewportSize());
    shader->setFloat(shader->vars.SunBrightness, sunVisibility);

    shader->setVector3(shader->vars.SunLight, sunLight);
    shader->setVector3(shader->vars.CameraPos, Camera::getPosition());

    shader->setTexture(shader->vars.Diffuse, textures.Diffuse);
    
    mesh->draw();
}