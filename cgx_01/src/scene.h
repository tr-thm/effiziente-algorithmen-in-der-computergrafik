#pragma once
#include <string>
#include <vector>

#include "entity.h"
#include "environment.h"

class Scene
{
    public:
    Scene(std::string filename);
    ~Scene();
    void update(const double time);

    private:
    std::vector<Entity*> entities;
};
