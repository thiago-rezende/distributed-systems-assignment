/**
 * @file producer.hpp
 * @author Thiago Rezende (thiago-rezende.github.io)
 * @brief Producer implementation
 * @version 0.1
 * @date 2021-01-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <third_implementation/base.hpp>

template <typename _Type>
class Producer
{
private:
    Buffer<_Type> *m_buffer;

public:
    Producer(Buffer<_Type> *buffer)
        : m_buffer(buffer) {}

    void Produce(ProducerFunction<_Type> function)
    {
        _Type value = function();
        m_buffer->push_back(value);
    }
};
