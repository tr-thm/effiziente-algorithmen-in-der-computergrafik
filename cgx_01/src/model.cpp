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

#include "filereader.h"
#include "model.h"

Model::Model(std::string filename)
{
    this->position = Vector3();
    this->rotation = Vector3();
    this->scale = Vector3();
    FileReader reader = FileReader(filename);
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "m")
        {
            //mesh
            std::string m = reader.getString();
            this->mesh = new Mesh(m);
        }
        else if (type == "s")
        {
            //shader
            std::string vs = reader.getString();
            std::string fs = reader.getString();
            this->shader = new Shader(vs, fs);
        }
        else if (type == "t")
        {
            //textures
            std::string slot = reader.getString();
            Texture *tex = new Texture(reader.getString());

            if (slot == "Diffuse") this->textures.Diffuse = tex;
            if (slot == "NormalMap") this->textures.NormalMap = tex;
            if (slot == "Roughness") this->textures.Roughness = tex;
        }
    }
}

void Model::render(Matrix projectionMatrix, Matrix viewMatrix, Vector3 sunLight, Vector3 cameraPosition)
{
    Vector3 pos = position;
    if (this->fixed)
    {
        pos = position + cameraPosition;
    }

    shader->activate();

    shader->setMatrix(shader->vars.ProjectionMatrix, projectionMatrix);
    shader->setMatrix(shader->vars.ViewMatrix, viewMatrix);
    shader->setMatrix(shader->vars.WorldMatrix, Matrix::translation(pos) * Matrix::rotation(rotation) * Matrix::scale(scale));
    shader->setVector3(shader->vars.SunLight, sunLight);
    shader->setVector3(shader->vars.CameraPos, cameraPosition);

    shader->setTexture(shader->vars.Diffuse, textures.Diffuse);
    shader->setTexture(shader->vars.NormalMap, textures.NormalMap);
    shader->setTexture(shader->vars.Roughness, textures.Roughness);
    
    mesh->draw();
}

bool Model::skipDepthTesting()
{
    return nodepth;
}

void Model::toggleFlag(std::string flag)
{
    if (flag == "fixed") this->fixed = !this->fixed;
    if (flag == "nodepth") this->nodepth = !this->nodepth;
}

void Model::setTransform(Vector3 position, Vector3 rotation, Vector3 scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

Model::~Model()
{
    delete mesh;
    delete shader;
    delete textures.Diffuse;
    delete textures.NormalMap;
    delete textures.Roughness;
}
