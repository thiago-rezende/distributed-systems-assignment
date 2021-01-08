/**
 * @file base.hpp
 * @author Thiago Rezende (thiago-rezende.github.io)
 * @brief Base definitions to all implementations
 * @version 0.1
 * @date 2021-01-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <second_implementation/pch.h>

/* Implementation typedefs */
template <typename _ReturnType>
using ProducerFunction = std::function<_ReturnType()>;

template <typename _BufferType>
using ConsumerFunction = std::function<void(_BufferType)>;

template <typename _Type>
using Buffer = std::deque<_Type>;

/* Implementation random number generator */
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);
std::normal_distribution<double> distribution(0.0, 255.0);

uint8_t random_number()
{
    return distribution(generator);
}
