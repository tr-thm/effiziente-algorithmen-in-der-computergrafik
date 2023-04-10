#pragma once

struct Settings
{
    bool fullscreen = false;
    int width = 1280;
    int height = 720;
    bool msaa = true;
    bool vsync = true;
    bool culling = true;
    bool depth = true;
    double walkSpeed = 1.0;
    double mouseSpeed = 1.0;
};