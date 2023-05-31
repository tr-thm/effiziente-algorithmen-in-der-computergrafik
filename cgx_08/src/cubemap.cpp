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

#include <cstdio>
#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "cubemap.h"
#include "threadpool.h"
#include "timer.h"

CubeMap::CubeMap(std::string filename)
{
    this->filename = filename;

    ThreadPool::run([this]()
    {
        Timer t = Timer("CubeMap");

        std::string filename1 = this->filename.substr(0, this->filename.length() - 4) + "_1.dds";
        std::string filename2 = this->filename.substr(0, this->filename.length() - 4) + "_2.dds";
        std::string filename3 = this->filename.substr(0, this->filename.length() - 4) + "_3.dds";
        std::string filename4 = this->filename.substr(0, this->filename.length() - 4) + "_4.dds";
        std::string filename5 = this->filename.substr(0, this->filename.length() - 4) + "_5.dds";
        std::string filename6 = this->filename.substr(0, this->filename.length() - 4) + "_6.dds";

		std::cout << "Loading " << this->filename << std::endl;
        this->data = this->loadFile(filename1, &this->width, &this->height, &this->format, &this->mipMapCount);
        this->data2 = this->loadFile(filename2, &this->width, &this->height, &this->format, &this->mipMapCount);
        this->data3 = this->loadFile(filename3, &this->width, &this->height, &this->format, &this->mipMapCount);
        this->data4 = this->loadFile(filename4, &this->width, &this->height, &this->format, &this->mipMapCount);
        this->data5 = this->loadFile(filename5, &this->width, &this->height, &this->format, &this->mipMapCount);
        this->data6 = this->loadFile(filename6, &this->width, &this->height, &this->format, &this->mipMapCount);

        t.stop();
    });
}

unsigned int CubeMap::getId()
{
    if (data && data2 && data3 && data4 && data5 && data6) load();
    return textureId;
}

void CubeMap::load()
{
    glActiveTexture(GL_TEXTURE15);
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 

    int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    int size = ((width+3)/4) * ((height+3)/4) * blockSize;
    
	glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, width, height, 0, size, data);
	glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, width, height, 0, size, data2);
	glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, width, height, 0, size, data3);
	glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, width, height, 0, size, data4);
	glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, width, height, 0, size, data5);
	glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, width, height, 0, size, data6);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    free(data);
    free(data2);
    free(data3);
    free(data4);
    free(data5);
    free(data6);
    data = nullptr;
    data2 = nullptr;
    data3 = nullptr;
    data4 = nullptr;
    data5 = nullptr;
    data6 = nullptr;
}

CubeMap* CubeMap::acquire(std::string filename)
{
    if (!cache.count(filename))
    {
        cache[filename] = new CubeMap(filename);
    }
    CubeMap* cubemap = (CubeMap*)cache[filename];
    cubemap->usageCount++;
    return cubemap;
}
