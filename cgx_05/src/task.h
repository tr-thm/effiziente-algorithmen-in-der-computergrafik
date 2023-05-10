#pragma once
#include <thread>
#include <future>

class Task
{
    public:
    template<class Function> static void runThread(Function&& f)
    {
        std::thread(f).detach();
    }
    template<class Function> static void runAsync(Function&& f)
    {
        auto futptr = std::make_shared<std::future<void>>();
        *futptr = std::async(std::launch::async, [futptr, f]() {
            f();
        });
    }
};