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

#pragma once
#include <map>
#include <string>

class Texture
{
    public:
        Texture(std::string filename);
        ~Texture();
        unsigned int getId();
        static Texture* acquire(std::string filename);
        static void release(Texture *tex);

    private:
        std::string filename;
        unsigned int width, height, format, mipMapCount;
        unsigned int textureId = 0;
        unsigned char *data = NULL;
        unsigned int usageCount = 0;
        void load();
        unsigned char *loadFile(std::string filename, unsigned int *x, unsigned int *y, unsigned int *format, unsigned int *mipMapCount);
        static inline std::map<std::string,Texture*> cache;
};
