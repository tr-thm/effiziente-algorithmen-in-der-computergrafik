#include <iostream>

#include "game.h"
#include "graphics.h"
#include "settings.h"
#include "window.h"

// void* operator new(size_t size)
// {
//     //std::cout << "Allocating " << size << " bytes." << std::endl;
//     return malloc(size);
// }

// void operator delete(void *memory, size_t zise)
// {
//     std::cout << "Freeingbytes." << std::endl;
//     free(memory);
// }

int main()
{
    std::cout << "Engine starting..." << std::endl;

    Settings settings;

    if (Window::create(settings) && Graphics::start(settings))
    {
        Game::load(settings);
        double dtime = 0;
        while (Window::loop(&dtime))
        {
            Game::loop(dtime);
            Graphics::loop();
        }
        Game::unload();
        Graphics::terminate();
        Window::destroy();
    }

    std::cout << "Engine terminated." << std::endl;

    return 0;
}