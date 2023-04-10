#pragma once
#include <string>

#include "math/vertex.h"

class Mesh
{
    public:
    Mesh(std::string);
    ~Mesh();
    void draw();

    private:
    unsigned int vertexAttributes, vertexBuffer;
    int vertexCount;
    void init(Vertex*, int);
};
