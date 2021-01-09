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

#include <second_implementation/pch.h>
#include <config.h>

#include <second_implementation/helpers.hpp>
#include <second_implementation/semaphore.hpp>

int main()
{
    /* Initialize Logger */
    Horus::Logger::Init();

    /* CMake Configured File Defines */
    H_INFO("PROJECT NAME => {}", "Producer Consumer - Second Implementation");
    H_INFO("PROJECT VERSION => {}", PROJECT_VERSION);

    /* Buffer maximum size */
    const uint8_t max_buffer_size = 10;

    /* Application buffer */
    std::deque<uint8_t> buffer;

    /* Application semaphore */
    Semaphore sem(1);

    /*Producer function */
    std::function<void()> producer = [&]() {
        while (true)
        {
            /* lock */
            sem.wait();

            /**
             * @brief Produce until buffer is full
             *
             */
            while (buffer.size() != max_buffer_size)
            {
                /* Generating random runber */
                uint8_t value = random_number();

                std::cout << "Produced " << static_cast<int>(value) << std::endl;

                /* Sending to buffer */
                buffer.push_back(value);

                /* Sleep for 200 miliseconds */
                using namespace std::literals;
                std::this_thread::sleep_for(200ms);
            }

            /* Release */
            sem.notify();
        }
    };

    /*Consumer function */
    std::function<void()> consumer = [&]() {
        while (true)
        {
            /* Lock */
            sem.wait();

            /**
             * @brief Consume until buffe is empty
             *
             */
            while (buffer.size() != 0)
            {
                /* Getting the next buffered value */
                uint8_t value = buffer.front();

                /* Removing from buffer */
                buffer.pop_front();

                std::cout << "Consumed " << static_cast<int>(value) << std::endl;

                /* Sleep for 200 miliseconds */
                using namespace std::literals;
                std::this_thread::sleep_for(200ms);
            }

            /* Release */
            sem.notify();
        }
    };

    /* Create producer and consumer threads */
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    /* Join porducer and consumer threads */
    producer_thread.join();
    consumer_thread.join();

    return 0;
}
