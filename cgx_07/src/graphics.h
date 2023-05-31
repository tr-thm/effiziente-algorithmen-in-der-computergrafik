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

#include "environment.h"
#include "model.h"
#include "settings.h"
#include "math/matrix.h"
#include "math/vector3.h"

class Graphics
{
    public:
        static int loadModel(std::string filename);
        static void updateModel(int id, Matrix transform);
        static void updateModel(int id, std::string flag);
        static void unloadModel(int id);
        static void setBackground(Vector3 color);
        static void setSun(Vector3 direction);
        static void setSky(std::string filename);
        static void loadEnvironment();
        static bool start(Settings props);
        static void loop();
        static void terminate();
        static void setWindowSize(int width, int height);

    private:
        static void setViewport();
        static inline Settings settings;
        static inline int viewportWidth = 0;
        static inline int viewportHeight = 0;
        static inline int resizeViewport = false;
        static inline std::map<int, Model*> models;
        static inline int modelId = 0;
        static inline Environment environment;
};
