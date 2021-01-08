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

    Buffer<uint8_t> buffer;
    Producer<uint8_t> p(&buffer);
    Consumer<uint8_t> c(&buffer);

    for (size_t i = 0; i < 5; i++)
    {
        p.Produce([]() {
            uint8_t value = random_number();
            std::cout << "Produced " << static_cast<int>(value) << std::endl;
            return value;
        });

        c.Consume([](uint8_t value) {
            std::cout << "Consumed " << static_cast<int>(value) << std::endl;
        });
    }

    return 0;
}
