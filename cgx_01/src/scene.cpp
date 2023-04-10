#include "filereader.h"
#include "graphics.h"
#include "scene.h"

Scene::Scene(std::string filename)
{
    FileReader reader = FileReader(filename);
    Environment env = Environment();
    while (reader.hasLine())
    {
        std::string type = reader.getString();
        if (type == "env")
        {
            std::string key = reader.getString();
            if (key == "background")
            {
                env.background = reader.getVector3();
            }
            else if (key == "sun")
            {
                env.sun = reader.getVector3();
            }
        }
        else if (type == "e")
        {
            entities.push_back(new Entity(reader.getString()));
        }
        else if (type == "m")
        {
            entities[entities.size() - 1]->setModel(reader.getString());
        }
        else if (type == "p")
        {
            entities[entities.size() - 1]->setPosition(reader.getVector3());
        }
        else if (type == "r")
        {
            entities[entities.size() - 1]->setRotation(reader.getVector3());
        }
        else if (type == "s")
        {
            entities[entities.size() - 1]->setScale(reader.getVector3());
        }
        else if (type == "f")
        {
            entities[entities.size() - 1]->addFlag(reader.getString());
        }
        else if (type == "l")
        {
            entities[entities.size() - 1]->addLogic(reader.getString());
        }
    }
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->load();
    }
    Graphics::setEnvironment(env);
}

Scene::~Scene()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
    entities.clear();
}

void Scene::update(const double time)
{
    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->update(time);
    }
}
