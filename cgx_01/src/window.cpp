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

#include <algorithm>
#include <iostream>

#include "game.h"
#include "graphics.h"
#include "window.h"

void Window::onError(int error, const char *description)
{
    std::cout << "Error: " << description << std::endl;
}

GLFWmonitor* Window::getCurrentMonitor()
{
    glfwGetWindowPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &width, &height);

    int monitorCount;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);

    int lastDelta = 0;
    GLFWmonitor* monitor;

    for (int i = 0; i < monitorCount; i++)
    {
        int monitorX, monitorY;
        glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);
        const GLFWvidmode *mode = glfwGetVideoMode(monitors[i]);

        int wx1 = xpos;
        int wx2 = xpos + width;
        int wy1 = ypos;
        int wy2 = ypos + height;

        int mx1 = monitorX;
        int mx2 = monitorX + mode->width;
        int my1 = monitorY;
        int my2 = monitorY + mode->height;

        int delta = std::max(0, std::min(wx2, mx2) - std::max(wx1, mx1))
                   * std::max(0, std::min(wy2, my2) - std::max(wy1, my1));

        if (delta > lastDelta)
        {
            lastDelta = delta;
            monitor = monitors[i];
        }
    }

    return monitor;
}

void Window::toggleFullscreen()
{
    if (isFullscreen)
    {
        glfwSetWindowMonitor(window, NULL, xpos, ypos, width, height, GLFW_DONT_CARE);
    }
    else
    {
        GLFWmonitor* monitor = getCurrentMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    isFullscreen = !isFullscreen;
}

void Window::onKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        if (isMouseCaptured)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isMouseCaptured = false;
        }
        else
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        toggleFullscreen();
    }
    else
    {
        Game::setKey(key, action);
    }
}

void Window::onFramebufferSizeChanged(GLFWwindow *window, int width, int height)
{
    Graphics::setWindowSize(width, height);
}

void Window::onMouseMoved(GLFWwindow *window, double xpos, double ypos)
{
    if (isMouseCaptured)
    {
        static double mouseLastX = xpos;
        static double mouseLastY = ypos;

        double deltaX = xpos - mouseLastX;
        double deltaY = ypos - mouseLastY;

        Game::setMouse(deltaX, deltaY, 0, 0);

        mouseLastX = xpos;
        mouseLastY = ypos;
    }
}

void Window::onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{
    if (isMouseCaptured)
    {
        Game::setMouse(0, 0, xoffset, yoffset);
    }
}

void Window::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (!isMouseCaptured && action == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        isMouseCaptured = true;
    }
}

void Window::printFps()
{
    static double previousTime = 0;
    static int frameCount = 0;
    
    double currentTime = glfwGetTime();
    if (currentTime - previousTime >= 1.0)
    {
        std::cout << "FPS: " << frameCount << std::endl;

        frameCount = 0;
        previousTime = currentTime;
    }
    frameCount++;
}

/**
 * Create a new windows.
 */
bool Window::create(Settings props)
{
    width = props.width;
    height = props.height;
    isFullscreen = props.fullscreen;

    glfwSetErrorCallback(onError);
    
    if (!glfwInit())
    {
        std::cout << "Error initilizing graphics.";
        return false;
    }

    if (props.msaa) glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (props.fullscreen)
    {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        window = glfwCreateWindow(mode->width, mode->height, "CGX", monitor, NULL);
    }
    else
    {
        window = glfwCreateWindow(props.width, props.height, "CGX", NULL, NULL);
    }
    if (!window)
    {
        glfwTerminate();
        std::cout << "Error opening window.";
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, onKeyboardInput);
    glfwSetFramebufferSizeCallback(window, onFramebufferSizeChanged);
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    Graphics::setWindowSize(w, h);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSetCursorPosCallback(window, onMouseMoved);
    glfwSetScrollCallback(window, onMouseWheel);
    glfwSetMouseButtonCallback(window, onMouseButton);
    isMouseCaptured = true;
    return true;
}

/**
 * Called once per frame. Handles Window Events and prepares
 */
bool Window::loop(double *time)
{
    if (glfwWindowShouldClose(window)) return false;

    glfwSwapBuffers(window);
    glfwPollEvents();
    printFps();

    double now = glfwGetTime();
    static double lastTime = now;
    *time = now - lastTime;
    lastTime = now;

    return true;
}

void Window::destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}