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

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "filereader.h"
#include "mesh.h"
#include "threadpool.h"
#include "timer.h"
#include "math/vector3.h"

Mesh::Mesh(std::string filename)
{
    this->filename = filename;
    ThreadPool::run([this]()
    {
        Timer t = Timer(this->filename);
        std::vector<Vector3> v;
        std::vector<Vector2> vt;
        std::vector<Vector3> vn;
        std::vector<std::string> f;

        FileReader reader = FileReader(this->filename);
        while (reader.hasLine())
        {
            std::string type = reader.getString();
            if (type == "v")
            {
                v.push_back(reader.getVector3());
            }
            else if (type == "vt")
            {
                vt.push_back(reader.getVector2());
            }
            else if (type == "vn")
            {
                vn.push_back(reader.getVector3());
            }
            else if (type == "f")
            {
                for (int i = 0; i < 3; i++)
                {
                    f.push_back(reader.getString());
                }
            }
        }
        //
        
        std::vector<Vertex> *vertices = new std::vector<Vertex>();
        for (int i = 0; i < f.size(); i++)
        {
            std::stringstream stream(f[i]);
            std::string item;
            std::vector<int> values;
            while (getline(stream, item, '/'))
            {
                values.push_back(stoi(item) - 1);
            }
            vertices->push_back(Vertex(v[values[0]], vt[values[1]], vn[values[2]]));
        }
        this->vertexCount = vertices->size();
        this->vertices = vertices;
        t.stop();
    });
}

void Mesh::init()
{
    vertexCount = vertices->size();
    glGenVertexArrays(1, &vertexAttributes);
    glBindVertexArray(vertexAttributes);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vertex), vertices->data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector2)));
    glEnableVertexAttribArray(2);
    delete this->vertices;
    this->vertices = nullptr;
}

void Mesh::draw()
{
    if (this->vertices) this->init();
    glBindVertexArray(vertexAttributes);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vertexAttributes);
    glDeleteBuffers(1, &vertexBuffer);
}

Mesh *Mesh::acquire(std::string filename)
{
    if (!cache.count(filename))
    {
        cache[filename] = new Mesh(filename);
    }
    cache[filename]->usageCount++;
    return cache[filename];
}

void Mesh::release(Mesh *mesh)
{
    if (mesh != nullptr)
    {
        std::string filename = mesh->filename;
        cache[filename]->usageCount--;
        if (cache[filename]->usageCount == 0)
        {
            delete cache[filename];
            cache.erase(filename);
        }
        mesh = nullptr;
    }
}
