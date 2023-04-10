#pragma once
#include <map>
#include <string>

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "math/vector3.h"

class Model
{
    public:
    Model(std::string filename);
    ~Model();
    void setTransform(Vector3, Vector3, Vector3);
    void toggleFlag(std::string flag);
    void render(Matrix projectionMatrix, Matrix viewMatrix, Vector3 sunLight, Vector3 cameraPosition);
    bool skipDepthTesting();

    private:
    bool nodepth = false;
    bool fixed = false;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    Shader *shader;
    Mesh *mesh;
    struct {
        Texture *Diffuse;
        Texture *NormalMap;
        Texture *Roughness;
    } textures;
};
