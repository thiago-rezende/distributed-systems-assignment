/**
 * @file main.cpp
 * @author Thiago Rezende (thiago-rezende.github.io)
 * @brief First Implementation EntryPoint
 * @version 0.1
 * @date 2021-01-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <first_implementation/pch.h>
#include <config.h>

#include <first_implementation/helpers.hpp>

int main()
{
    /* Initialize Logger */
    Horus::Logger::Init();

    /* CMake Configured File Defines */
    H_INFO("PROJECT NAME => {}", "Producer Consumer - First Implementation");
    H_INFO("PROJECT VERSION => {}", PROJECT_VERSION);

    /* Application buffer */
    std::deque<uint8_t> buffer;

    /* Producer function */
    std::function<void()> producer = [&]() {
        /* Getting thread id */
        std::stringstream ss;
        ss << std::this_thread::get_id();
        std::string thread_id = ss.str();

        H_DEBUG("Producer#{} started", thread_id);

        /* Generating random number */
        H_DEBUG("Producer#{} generating random value", thread_id);
        uint8_t value = random_number();

        H_DEBUG("Producer#{} sending value to buffer", thread_id);
        buffer.push_back(value);

        std::cout << "Thread#" << thread_id << " Produced " << static_cast<int>(value) << std::endl;

        /* Sleep for 200 miliseconds */
        H_DEBUG("Producer#{} sleeping", thread_id);
        using namespace std::literals;
        std::this_thread::sleep_for(200ms);
    };

    /* Consumer function */
    std::function<void()> consumer = [&]() {
        /* Getting thread id */
        std::stringstream ss;
        ss << std::this_thread::get_id();
        std::string thread_id = ss.str();

        H_DEBUG("Conusmer#{} started", thread_id);

        /* Getting the next buffered value */
        H_DEBUG("Consumer#{} getting next buffered value", thread_id);
        uint8_t value = buffer.front();

        H_DEBUG("Consumer#{} removing consumed value from buffer", thread_id);
        buffer.pop_front();

        std::cout << "Thread#" << thread_id << " Consumed " << static_cast<int>(value) << std::endl;

        /* Sleep for 200 miliseconds */
        H_DEBUG("Consumer#{} sleeping", thread_id);
        using namespace std::literals;
        std::this_thread::sleep_for(200ms);
    };

    /**
     * @brief Sequential produce and consume
     *
     */
    while (true)
    {
        /**
         * @brief Produce a random number and send to buffer
         *
         */
        producer();

        /**
         * @brief Consumes the next buffered value
         *
         */
        consumer();
    }

    return 0;
}
