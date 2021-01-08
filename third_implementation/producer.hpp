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

/**
 * @brief Producer class
 *
 * @tparam _Type Data type to produce
 */
template <typename _Type>
class Producer
{
private:
    /**
     * @brief Buffer to store produced values
     *
     */
    Buffer<_Type> *m_buffer;

public:
    /**
     * @brief Construct a new Producer object
     *
     * @param buffer Pointer to data buffer
     */
    Producer(Buffer<_Type> *buffer)
        : m_buffer(buffer) {}

    /**
     * @brief Produces the data and send to buffer
     *
     * @param function Function to handle data production
     */
    void Produce(ProducerFunction<_Type> function)
    {
        _Type value = function();
        m_buffer->push_back(value);
    }
};
