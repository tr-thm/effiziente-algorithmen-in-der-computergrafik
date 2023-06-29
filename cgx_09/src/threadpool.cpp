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

#include <iostream>

#include "threadpool.h"

void ThreadPool::create()
{
    const unsigned int num_threads = std::thread::hardware_concurrency();
    threads.resize(num_threads);
    std::cout << "Create thread pool with " << num_threads << " threads." << std::endl;
    for (unsigned int i = 0; i < num_threads; i++)
    {
        threads[i] = std::thread(process);
    }
}

void ThreadPool::process()
{
    while (true)
    {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            mutex_condition.wait(lock, [] {
                return !jobs.empty() || !active;
            });
            if (!active) return;
            job = jobs.front();
            jobs.pop();
        }
        job();
    }
}

void ThreadPool::run(const std::function<void()>& job)
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        jobs.push(job);
    }
    mutex_condition.notify_one();
}

void ThreadPool::terminate()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        active = false;
    }
    mutex_condition.notify_all();
    for (std::thread& thread : threads)
    {
        thread.join();
    }
    threads.clear();
}