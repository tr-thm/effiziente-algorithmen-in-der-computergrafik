#include <fstream>
#include <sstream>
#include <string>

#include "math/vector2.h"
#include "math/vector3.h"

struct FileReader
{
    FileReader(std::string filename);
    bool hasLine();
    std::string getString();
    float getFloat();
    Vector2 getVector2();
    Vector3 getVector3();

    std::string filename;
    int line = 0;
    std::ifstream fileStream;
    std::istringstream lineStream;
};
