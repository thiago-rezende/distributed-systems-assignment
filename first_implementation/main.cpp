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
        uint8_t value = random_number();
        buffer.push_back(value);

        std::cout << "Produced " << static_cast<int>(value) << std::endl;

        /* Sleep for 200 miliseconds */
        using namespace std::literals;
        std::this_thread::sleep_for(200ms);
    };

    /* Consumer function */
    std::function<void()> consumer = [&]() {
        uint8_t value = buffer.front();
        buffer.pop_front();

        std::cout << "Consumed " << static_cast<int>(value) << std::endl;

        /* Sleep for 200 miliseconds */
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
