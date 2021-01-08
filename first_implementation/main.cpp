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

#include <first_implementation/base.hpp>
#include <first_implementation/producer.hpp>
#include <first_implementation/consumer.hpp>

int main()
{
    /* Initialize Logger */
    Horus::Logger::Init();

    /* CMake Configured File Defines */
    H_INFO("PROJECT NAME => {}", "Producer Consumer - First Implementation");
    H_INFO("PROJECT VERSION => {}", PROJECT_VERSION);

    /* Application buffer */
    Buffer<uint8_t> buffer;

    /* Producer and Consumer */
    Producer<uint8_t> p(&buffer);
    Consumer<uint8_t> c(&buffer);

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
        p.Produce([]() {
            /* Generating random number */
            uint8_t value = random_number();

            std::cout << "Produced " << static_cast<int>(value) << std::endl;

            /* Sleep for 200 miliseconds */
            using namespace std::literals;
            std::this_thread::sleep_for(200ms);

            /* Returns the value to store in buffer */
            return value;
        });

        /**
         * @brief Consumes the next buffered value
         *
         */
        c.Consume([](uint8_t value) {
            std::cout << "Consumed " << static_cast<int>(value) << std::endl;

            /* Sleep for 200 miliseconds */
            using namespace std::literals;
            std::this_thread::sleep_for(200ms);
        });
    }

    return 0;
}
