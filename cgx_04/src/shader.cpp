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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

Shader::Shader(std::string vertexShaderFile, std::string fragmentShaderFile)
{
    int success;
    char infoLog[512];

    this->filenames = { vertexShaderFile, fragmentShaderFile };

    unsigned int vertexShader, fragmentShader;
    if (!shaderCompile(vertexShaderFile, &vertexShader, GL_VERTEX_SHADER))
    {
        return;
    }

    if (!shaderCompile(fragmentShaderFile, &fragmentShader, GL_FRAGMENT_SHADER))
    {
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Failed to link shader program" << std::endl << infoLog << std::endl;
        return;
    }

    this->vars = {
        glGetUniformLocation(shaderProgram, "WorldMatrix"),
        glGetUniformLocation(shaderProgram, "ViewMatrix"),
        glGetUniformLocation(shaderProgram, "ProjectionMatrix"),
        glGetUniformLocation(shaderProgram, "SunLight"),
        glGetUniformLocation(shaderProgram, "CameraPos"),
        glGetUniformLocation(shaderProgram, "Diffuse"),
        glGetUniformLocation(shaderProgram, "NormalMap"),
        glGetUniformLocation(shaderProgram, "Roughness")
    };

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate()
{
    glUseProgram(shaderProgram);
}

void Shader::setMatrix(int location, Matrix m)
{
    if (location < 0) return;
    glUniformMatrix4fv(location, 1, GL_FALSE, (float*)&m);
}

void Shader::setVector3(int location, Vector3 v)
{
    if (location < 0) return;
    glUniform3fv(location, 1, (float*)&v);
}

void Shader::setTexture(int location, Texture *texture)
{
    if (location < 0) return;
    if (texture == nullptr) return;

    if (location == vars.Diffuse)
    {
        glUniform1i(location, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getId());
    }
    else if (location == vars.NormalMap)
    {
        glUniform1i(location, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture->getId());
    }
    else if (location == vars.Roughness)
    {
        glUniform1i(location, 2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture->getId());
    }
}

bool Shader::shaderCompile(std::string filename, unsigned int *shader, unsigned int type)
{
    char *shaderSource = readFile(filename);

    int success;
    char infoLog[512];

    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        std::cout << "Failed to compile shader: " << filename << std::endl << infoLog << std::endl;
        return false;
    }
    return true;
}

char *Shader::readFile(std::string filename)
{
    char *shaderSource = 0;
    long length;
    FILE *f = fopen (filename.c_str(), "rb");

    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        shaderSource = (char*)malloc (length+1);
        if (shaderSource)
        {
            fread (shaderSource, 1, length, f);
            shaderSource[length] = '\0';
        }
        fclose (f);
        return shaderSource;
    }
    return 0;
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}

Shader *Shader::acquire(std::string vertexShaderFile, std::string fragmentShaderFile)
{
    std::pair<std::string, std::string> filenames = { vertexShaderFile, fragmentShaderFile };
    if (!cache.count(filenames))
    {
        cache[filenames] = new Shader(vertexShaderFile, fragmentShaderFile);
    }
    cache[filenames]->usageCount++;
    return cache[filenames];
}

void Shader::release(Shader *shader)
{
    if (shader != nullptr)
    {
        std::pair<std::string, std::string> filenames = shader->filenames;
        cache[filenames]->usageCount--;
        if (cache[filenames]->usageCount == 0)
        {
            delete cache[filenames];
            cache.erase(filenames);
        }
        shader = nullptr;
    }
}
