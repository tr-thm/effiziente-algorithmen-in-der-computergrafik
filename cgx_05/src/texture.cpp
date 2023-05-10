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
 * 
 * -------------------------------------------------------------------------
 * 
 * Part of this code is based on Cody Tilkins C OpenGL DDS Loading Tutorial:
 * https://gist.github.com/tilkinsc/13191c0c1e5d6b25fbe79bbd2288a673
 * 
*/

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "threadpool.h"
#include "timer.h"

Texture::Texture(std::string filename)
{
    this->filename = filename;

    ThreadPool::run([this]()
    {
        Timer t = Timer(this->filename);

        this->data = this->loadFile(this->filename, &this->width, &this->height, &this->format, &this->mipMapCount);

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

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount - 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;

	int w = width;
	int h = height;
	int size = 0;
	int offset = 0;

	for (int i = 0; i < mipMapCount; i++)
	{
		if(w == 0 || h == 0)
		{
			mipMapCount--;
			continue;
		}
		size = ((w+3)/4) * ((h+3)/4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, i, format, w, h, 0, size, data + offset);
		offset += size;
		w /= 2;
		h /= 2;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount - 1);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] data;
    data = nullptr;
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

unsigned char * Texture::loadFile(std::string filename, unsigned int *width, unsigned int *height, unsigned int *format, unsigned int *mipMapCount)
{   
	if (!std::filesystem::exists(filename)) return nullptr;

	long size = std::filesystem::file_size(filename);
	std::ifstream file(filename, std::ios::binary);
	if (!file) return nullptr;

	unsigned char *header = new unsigned char[128];
	file.read(reinterpret_cast<char*>(&header[0]), 128);
	if (memcmp(header, "DDS ", 4) != 0) return nullptr;

	*height      = (header[12]) | (header[13] << 8) | (header[14] << 16) | (header[15] << 24);
	*width       = (header[16]) | (header[17] << 8) | (header[18] << 16) | (header[19] << 24);
	*mipMapCount = (header[28]) | (header[29] << 8) | (header[30] << 16) | (header[31] << 24);

	if (memcmp(&header[84], "DXT1", 4) == 0) *format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	if (memcmp(&header[84], "DXT3", 4) == 0) *format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	if (memcmp(&header[84], "DXT5", 4) == 0) *format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	
	delete[] header;
	
	unsigned char *data = new unsigned char[size - 128];
	file.read(reinterpret_cast<char*>(&data[0]), size - 128);
	file.close();

    return data;
}
