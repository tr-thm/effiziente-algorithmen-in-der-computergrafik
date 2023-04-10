#pragma once
#include <string>
#include <vector>

#include "logic.h"
#include "math/vector3.h"

class Entity
{
    public:
    Entity(std::string name);
    ~Entity();
    void setModel(std::string model);
    void setPosition(Vector3 position);
    void setRotation(Vector3 rotation);
    void setScale(Vector3 scale);
    void addFlag(std::string flag);
    void addLogic(std::string logic);
    void load();
    void update(double time);

    private:
    int modelId;
    std::string name;
    std::string model;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale = Vector3(1,1,1);
    std::vector<std::string> flags;
    std::vector<LogicFunction> logic;
};
