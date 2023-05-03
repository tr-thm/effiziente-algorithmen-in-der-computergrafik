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
#include <GLFW/glfw3.h>

#include "settings.h"

class Window
{
    public:
        static bool create(Settings props);
        static bool loop(double *time);
        static void destroy();

    private:
        static void onError(int error, const char *description);
        static GLFWmonitor *getCurrentMonitor();
        static void toggleFullscreen();
        static void onKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void onFramebufferSizeChanged(GLFWwindow *window, int width, int height);
        static void onMouseMoved(GLFWwindow *window, double xpos, double ypos);
        static void onMouseWheel(GLFWwindow *window, double xoffset, double yoffset);
        static void onMouseButton(GLFWwindow *window, int button, int action, int mods);
        static void printFps();
        static inline GLFWwindow *window;
        static inline int width, height, xpos, ypos;
        static inline bool isFullscreen;
        static inline bool isMouseCaptured;
};
