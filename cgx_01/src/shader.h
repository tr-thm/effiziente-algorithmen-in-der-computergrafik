#pragma once
#include <string>

#include "texture.h"
#include "math/matrix.h"
#include "math/vector3.h"

class Shader
{
    public:
    Shader(std::string vertexShaderFile, std::string fragmentShaderFile);
    ~Shader();
    void activate();
    void setMatrix(int, Matrix);
    void setVector3(int, Vector3);
    void setTexture(int, Texture*);
    struct {
        int WorldMatrix;
        int ViewMatrix;
        int ProjectionMatrix;
        int SunLight;
        int CameraPos;
        int Diffuse;
        int NormalMap;
        int Roughness;
    } vars;

    private:
    unsigned int shaderProgram;
    bool shaderCompile(std::string filename, unsigned int *shader, unsigned int type);
    char *readFile(std::string filename);
};
