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

/**
 * @brief Consumer class
 *
 * @tparam _Type Data type to consume
 */
template <typename _Type>
class Consumer
{
private:
    /**
     * @brief Buffer to consume from
     *
     */
    Buffer<_Type> *m_buffer;

public:
    /**
     * @brief Construct a new Consumer object
     *
     * @param buffer Pointer to data buffer
     */
    Consumer(Buffer<_Type> *buffer)
        : m_buffer(buffer) {}

    /**
     * @brief Consumes the next buffered data
     *
     * @param function Function to handle data consumption
     */
    void Consume(ConsumerFunction<_Type> function)
    {
        function(m_buffer->front());
        m_buffer->pop_front();
    }
};
