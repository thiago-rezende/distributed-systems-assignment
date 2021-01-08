/**
 * @file semaphore.hpp
 * @author Thiago Rezende (thiago-rezende.github.io)
 * @brief Simple semaphore implementation
 * @version 0.1
 * @date 2021-01-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <second_implementation/pch.h>

class Semaphore
{
public:
    Semaphore(int count = 0)
        : m_count(count) {}

    inline void notify()
    {
        std::unique_lock<std::mutex> loculk(m_mut);
        m_count++;
        m_cv.notify_one();
    }

    inline void wait()
    {
        std::unique_lock<std::mutex> ul(m_mut);

        while (m_count == 0)
        {
            m_cv.wait(ul);
        }
        m_count--;
    }

private:
    std::mutex m_mut;
    std::condition_variable m_cv;
    int m_count;
};
