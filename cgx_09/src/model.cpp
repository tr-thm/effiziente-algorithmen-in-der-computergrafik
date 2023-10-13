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

#include "camera.h"
#include "filereader.h"
#include "model.h"

Model::Model(std::string filename)
{
    FileReader reader = FileReader(filename);
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "m")
        {
            //mesh
            std::string m = reader.getString();
            mesh = Mesh::acquire(m);
        }
        else if (type == "s")
        {
            //shader
            std::string vs = reader.getString();
            std::string fs = reader.getString();
            shader = Shader::acquire(vs, fs);
        }
        else if (type == "t")
        {
            //textures
            std::string slot = reader.getString();
            std::string filename = reader.getString();
            if (slot == "Diffuse")
            {
                textures.Diffuse = Texture::acquire(filename);
            }
            else if (slot == "NormalMap")
            {
                textures.NormalMap = Texture::acquire(filename);
            }
            else if (slot == "Roughness")
            {
                textures.Roughness = Texture::acquire(filename);
            }
            else if (slot == "Skybox")
            {
                textures.Skybox = CubeMap::acquire(filename);
            }
            else if (slot == "AR")
            {
                textures.AR = Texture::acquire(filename);
            }
            else if (slot == "NOM")
            {
                textures.NOM = Texture::acquire(filename);
            }
            else if (slot == "PMDG")
            {
                textures.PMDG = Texture::acquire(filename);
            }
        }
    }
}

void Model::render(Vector3 sunLight)
{
    shader->activate();

    shader->setMatrix(shader->vars.ProjectionMatrix, Camera::getProjectionMatrix());
    shader->setMatrix(shader->vars.ViewMatrix, Camera::getViewMatrix(fixed));
    shader->setMatrix(shader->vars.WorldMatrix, worldMatrix);
    shader->setVector3(shader->vars.SunLight, sunLight);
    shader->setVector3(shader->vars.CameraPos, Camera::getPosition());

    shader->setTexture(shader->vars.Diffuse, textures.Diffuse);
    shader->setTexture(shader->vars.NormalMap, textures.NormalMap);
    shader->setTexture(shader->vars.Roughness, textures.Roughness);
    
    shader->setTexture(shader->vars.AR, textures.AR);
    shader->setTexture(shader->vars.NOM, textures.NOM);
    shader->setTexture(shader->vars.PMDG, textures.PMDG);

    shader->setTexture(shader->vars.Skybox, textures.Skybox);
    
    mesh->draw();
}

bool Model::skipDepthTesting()
{
    return nodepth;
}

void Model::toggleFlag(std::string flag)
{
    if (flag == "fixed") fixed = !fixed;
    if (flag == "nodepth") nodepth = !nodepth;
}

void Model::setTransform(Matrix m)
{
    worldMatrix = m;
}

Model::~Model()
{
    Mesh::release(mesh);
    Shader::release(shader);
    Texture::release(textures.Diffuse);
    Texture::release(textures.NormalMap);
    Texture::release(textures.Roughness);
    CubeMap::release(textures.Skybox);
    Texture::release(textures.AR);
    Texture::release(textures.NOM);
    Texture::release(textures.PMDG);
}
