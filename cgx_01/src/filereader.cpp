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

#include "filereader.h"

FileReader::FileReader(std::string filename)
{
    this->filename = filename;
    fileStream.open(filename);
}

bool FileReader::hasLine()
{
    std::string lineBuffer;
    if (getline(fileStream, lineBuffer))
    {
        lineStream.clear();
        lineStream.str(lineBuffer);
        line++;
        return true;
    }
    lineStream.clear();
    fileStream.close();
    return false;
}

std::string FileReader::getString()
{
    std::string str;
    lineStream >> str;
    return str;
}

Vector2 FileReader::getVector2()
{
    try
    {
        std::string p1, p2;
        lineStream >> p1 >> p2;
        return (Vector2){stof(p1), stof(p2)};
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error in " << filename << " on line " << line << std::endl;
        std::cerr << e.what() << std::endl;
        return Vector2();
    }
}

Vector3 FileReader::getVector3()
{
    try
    {
        std::string p1, p2, p3;
        lineStream >> p1 >> p2 >> p3;
        return (Vector3){stof(p1), stof(p2), stof(p3)};
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error in " << filename << " on line " << line << std::endl;
        std::cerr << e.what() << std::endl;
        return Vector3();
    }
}

float FileReader::getFloat()
{
    try
    {
        std::string p1;
        lineStream >> p1;
        return stof(p1);
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error in " << filename << " on line " << line << std::endl;
        std::cerr << e.what() << std::endl;
        return 0.0;
    }
}
