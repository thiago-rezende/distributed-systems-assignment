/**
 * @file consumer.hpp
 * @author Thiago Rezende (thiago-rezende.github.io)
 * @brief Consumer implementation
 * @version 0.1
 * @date 2021-01-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <second_implementation/base.hpp>

template <typename _Type>
class Consumer
{
private:
    Buffer<_Type> *m_buffer;

public:
    Consumer(Buffer<_Type> *buffer)
        : m_buffer(buffer) {}

    void Consume(ConsumerFunction<_Type> function)
    {
        function(m_buffer->front());
        m_buffer->pop_front();
    }
};
