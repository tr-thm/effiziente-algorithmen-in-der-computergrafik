#pragma once
#include <string>

struct Texture
{
    Texture(std::string filename);
    ~Texture();
    unsigned int Id;
};
