#pragma once
#include <GLFW/glfw3.h>

#include "settings.h"

class Window
{
    public:
        static bool create(Settings);
        static bool loop(double*);
        static void destroy();

    private:
        static void onError(int error, const char *description);
        static GLFWmonitor* getCurrentMonitor();
        static void toggleFullscreen();
        static void onKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void onFramebufferSizeChanged(GLFWwindow *window, int width, int height);
        static void onMouseMoved(GLFWwindow *window, double xpos, double ypos);
        static void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset);
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void printFps();
        static inline GLFWwindow *window;
        static inline int width, height, xpos, ypos;
        static inline bool isFullscreen;
        static inline bool isMouseCaptured;
};
