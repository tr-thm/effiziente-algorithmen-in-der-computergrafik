#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "filereader.h"
#include "mesh.h"
#include "math/vector3.h"

Mesh::Mesh(std::string filename)
{
    std::vector<Vector3> v;
    std::vector<Vector2> vt;
    std::vector<Vector3> vn;
    std::vector<std::string> f;

    FileReader reader = FileReader(filename);
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
    std::vector<Vertex> vertices;
    for (int i = 0; i < f.size(); i++)
    {
        std::stringstream stream(f[i]);
        std::string item;
        std::vector<int> values;
        while (getline(stream, item, '/'))
        {
            values.push_back(stoi(item) - 1);
        }
        vertices.push_back((Vertex){ v[values[0]], vt[values[1]], vn[values[2]] });
    }
    init(reinterpret_cast<Vertex*>(vertices.data()), vertices.size());
}

void Mesh::init(Vertex *vertices, int vc)
{
    vertexCount = vc;
    glGenVertexArrays(1, &vertexAttributes);
    glBindVertexArray(vertexAttributes);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) + sizeof(Vector2)));
    glEnableVertexAttribArray(2);
}

void Mesh::draw()
{
    glBindVertexArray(vertexAttributes);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vertexAttributes);
    glDeleteBuffers(1, &vertexBuffer);
}