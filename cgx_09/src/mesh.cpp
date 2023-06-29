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
#include <unordered_map>
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
        std::vector<Vertex> *vertices = new std::vector<Vertex>();
        std::vector<unsigned int> *indices = new std::vector<unsigned int>();
        std::unordered_map<Vertex, unsigned int, VertexHashFunction> map;

        std::vector<Vector3> v;
        std::vector<Vector2> vt;
        std::vector<Vector3> vn;

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
                std::vector<int> vi1 = reader.getVertex();
                std::vector<int> vi2 = reader.getVertex();
                std::vector<int> vi3 = reader.getVertex();

                Vertex verts[3] = {
                    Vertex(v[vi1[0]], vt[vi1[1]], vn[vi1[2]]),
                    Vertex(v[vi2[0]], vt[vi2[1]], vn[vi2[2]]),
                    Vertex(v[vi3[0]], vt[vi3[1]], vn[vi3[2]])
                };

                for (int i = 0; i < 3; i++)
                {
                    unsigned int &index = map[verts[i]];
                    if (!index)
                    {
                        vertices->push_back(verts[i]);
                        index = vertices->size();
                    }
                    indices->push_back(index-1);
                }
            }
        }
        map.clear();
        for (int i = 0; i < indices->size(); i+=3)
        {
            Vertex& v1 = vertices->at(indices->at(i+0));
            Vertex& v2 = vertices->at(indices->at(i+1));
            Vertex& v3 = vertices->at(indices->at(i+2));
            
            Vertex::computeTangents(v1, v2, v3);
        }
        for (int i = 0; i < vertices->size(); i++)
        {
            Vertex& v1 = vertices->at(i);
            v1.tangent.normalize();
        }
        
        std::cout << "Done " << this->filename << " Vertices: " << vertices->size() << " Indices: " << indices->size() << std::endl;
        this->indexCount = indices->size();
        this->indices = indices;
        this->vertexCount = vertices->size();
        this->vertices = vertices;
        t.stop();
    });
}

void Mesh::init()
{
    glGenVertexArrays(1, &vertexAttributes);
    glBindVertexArray(vertexAttributes);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), indices->data(), GL_STATIC_DRAW);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vertex), vertices->data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector2)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector2) + sizeof(Vector3)));
    glEnableVertexAttribArray(3);
    delete vertices;
    vertices = nullptr;
    delete indices;
    indices = nullptr;
}

void Mesh::draw()
{
    if (vertices) init();
    glBindVertexArray(vertexAttributes);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void *)0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vertexAttributes);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
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
