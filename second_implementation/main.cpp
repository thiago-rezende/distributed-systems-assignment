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

#include <second_implementation/base.hpp>
#include <second_implementation/semaphore.hpp>
#include <second_implementation/producer.hpp>
#include <second_implementation/consumer.hpp>

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
    Buffer<uint8_t> buffer;

    /* Producer and Consumer */
    Producer<uint8_t> p(&buffer);
    Consumer<uint8_t> c(&buffer);

    /* Application semaphore */
    Semaphore sem(1);

    /* Producer thread function */
    std::function<void()> producer_thread_function = [&]() {
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
                p.Produce([]() {
                    uint8_t value = random_number();
                    std::cout << "Produced " << static_cast<int>(value) << std::endl;

                    /* Sleep for 200 miliseconds */
                    using namespace std::literals;
                    std::this_thread::sleep_for(200ms);
                    return value;
                });
            }

            /* Release */
            sem.notify();
        }
    };

    /* Conusumer thread function */
    std::function<void()> consumer_thread_function = [&]() {
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
                c.Consume([](uint8_t value) {
                    std::cout << "Consumed " << static_cast<int>(value) << std::endl;

                    /* Sleep for 200 miliseconds */
                    using namespace std::literals;
                    std::this_thread::sleep_for(200ms);
                });
            }

            /* Release */
            sem.notify();
        }
    };

    /* Create producer and consumer threads */
    std::thread producer_thread(producer_thread_function);
    std::thread consumer_thread(consumer_thread_function);

    /* Join porducer and consumer threads */
    producer_thread.join();
    consumer_thread.join();

    return 0;
}
