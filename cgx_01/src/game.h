#pragma once
#include <vector>

#include "scene.h"
#include "settings.h"
#include "math/vector3.h"

class Game
{
    public:
        static void setKey(int key, int state);
        static bool getKey(int key);
        static void setMouse(double dx, double dy, double sx, double sy);
        static void pushScene(std::string filename);
        static void popScene();
        static void load(Settings settings);
        static void loop(const double &time);
        static void unload();

    private:
        static inline bool gameKeyState[384] = {};
        static inline Vector3 cameraPosition = Vector3(7.3589, -6.9258, 4.9583);
        static inline Vector3 cameraRotation = Vector3::FromDegrees(63.6,  0.0, 46.7);
        static inline double walkSpeed = 3.0;
        static inline double mouseSpeed = 0.001;
        static inline Scene* scene;
};
