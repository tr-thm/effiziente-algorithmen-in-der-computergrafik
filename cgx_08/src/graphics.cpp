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

#include <iostream>

#include <glad.c>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "graphics.h"

void Graphics::setViewport()
{
    if (resizeViewport)
    {
        resizeViewport = false;

        glViewport(0,0, viewportWidth, viewportHeight);
        double aspect = (double)viewportWidth / (double)viewportHeight;
        Camera::setAspectRatio(aspect);
    }
}

int Graphics::loadModel(std::string filename)
{
    if (filename == "") return -1;
    int id = modelId++;
    Model *m = new Model(filename);
    models[id] = m;
    return id;
}

void Graphics::updateModel(int id, Matrix m)
{
    if (id >= 0 && models.count(id))
    {
        models[id]->setTransform(m);
    }
}

void Graphics::updateModel(int id, std::string flag)
{
    if (id >= 0 && models.count(id))
    {
        models[id]->toggleFlag(flag);
    }
}

void Graphics::unloadModel(int id)
{
    if (id >= 0 && models.count(id))
    {
        delete models[id];
        models.erase(id);
    }
}

void Graphics::setBackground(Vector3 background)
{
    environment.background = background;
}

void Graphics::setSun(Vector3 direction)
{
    environment.sunDirection = direction;
}

void Graphics::setSky(std::string filename)
{
    environment.sky = filename;
}

void Graphics::loadEnvironment()
{
    environment.load();
}

bool Graphics::start(Settings props)
{
    settings = props;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    
    glfwSwapInterval(props.vsync ? 1 : 0);
    if (settings.msaa) glEnable(GL_MULTISAMPLE);
    if (settings.culling) glEnable(GL_CULL_FACE);
    if (settings.depth) glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f,0.0f,0.0f,1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    return true;
}

void Graphics::loop()
{
    setViewport();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto &[key, model] : models)
    {
        if (settings.depth && model->skipDepthTesting())
        {
            glDisable(GL_DEPTH_TEST);
            model->render(environment.sunDirection);
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            model->render(environment.sunDirection);
        }
    }
    environment.render();
}

void Graphics::terminate()
{
    for (const auto &[key, model] : models)
    {
        delete model;
    }
    models.clear();
    environment.unload();
}

void Graphics::setWindowSize(int width, int height)
{
    std::cout << "Resolution: " << width << "x" << height << std::endl;
    viewportWidth = width;
    viewportHeight = height;
    resizeViewport = true;
}

Vector3 Graphics::getViewportSize()
{
    return Vector3(viewportWidth, viewportHeight, 0);
}
