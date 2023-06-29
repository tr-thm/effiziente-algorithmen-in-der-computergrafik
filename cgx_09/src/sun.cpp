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
#include <iostream>

#include "camera.h"
#include "sun.h"
#include "math/matrix.h"

Sun::Sun()
{
    this->mesh = Mesh::acquire("meshes/sun.obj");
    this->shader = Shader::acquire("shaders/vertex_shader_sun.glsl", "shaders/fragment_shader_sun.glsl");

    this->worldMatrix = Matrix::translation(Vector3(-10, 10, 5)) * Matrix::scale(Vector3(0.1, 0.1, 0.1));
    this->fixed = true;

    glGenQueries(1, &glQueryID);
}

void Sun::render()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glBeginQuery(GL_SAMPLES_PASSED, glQueryID);

    shader->activate();

    shader->setMatrix(shader->vars.ProjectionMatrix, Camera::getProjectionMatrix());
    shader->setMatrix(shader->vars.ViewMatrix, Camera::getViewMatrix(fixed));
    shader->setMatrix(shader->vars.WorldMatrix, worldMatrix);

    shader->setTexture(shader->vars.Diffuse, textures.Diffuse);
    
    mesh->draw();

    glEndQuery(GL_SAMPLES_PASSED);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLuint result;
    glGetQueryObjectuiv(glQueryID, GL_QUERY_RESULT, &result);
    visibility = fmin(result / 108.0, 1.0);
}