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
    catch(const std::exception& e)
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
    catch(const std::exception& e)
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
    catch(const std::exception& e)
    {
        std::cerr << "Error in " << filename << " on line " << line << std::endl;
        std::cerr << e.what() << std::endl;
        return 0.0;
    }
}
