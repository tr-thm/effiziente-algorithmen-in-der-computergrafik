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

#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "texture.h"
#include "threadpool.h"
#include "timer.h"

Texture::Texture(std::string filename)
{
    this->filename = filename;

    ThreadPool::run([this]()
    {
        Timer t = Timer(this->filename);
        stbi_set_flip_vertically_on_load(true);
        this->data = stbi_load(this->filename.c_str(), &this->width, &this->height, &this->channels, 0);
        t.stop();
    });
}

unsigned int Texture::getId()
{
    if (data) load();
    return textureId;
}

void Texture::load()
{
    glActiveTexture(GL_TEXTURE15);
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (this->channels == 1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->width, this->height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    }
    else if (this->channels == 3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if (this->channels == 4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
    data = NULL;
}

Texture::~Texture()
{
    glDeleteTextures(1, &this->textureId);
    this->textureId = 0;
}

Texture* Texture::acquire(std::string filename)
{
    if (!cache.count(filename))
    {
        cache[filename] = new Texture(filename);
    }
    cache[filename]->usageCount++;
    return cache[filename];
}

void Texture::release(Texture *tex)
{
    if (tex != nullptr)
    {
        std::string filename = tex->filename;
        cache[filename]->usageCount--;
        if (cache[filename]->usageCount == 0)
        {
            delete cache[filename];
            cache.erase(filename);
        }
        tex = nullptr;
    }
}