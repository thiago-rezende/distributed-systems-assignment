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
#include <second_implementation/producer.hpp>
#include <second_implementation/consumer.hpp>

int main()
{
    /* Initialize Logger */
    Horus::Logger::Init();

    /* CMake Configured File Defines */
    H_INFO("PROJECT NAME => {}", "Producer Consumer - Second Implementation");
    H_INFO("PROJECT VERSION => {}", PROJECT_VERSION);

    const uint8_t max_buffer_size = 10;
    Buffer<uint8_t> buffer;
    Producer<uint8_t> p(&buffer);
    Consumer<uint8_t> c(&buffer);

    std::mutex mut;
    std::condition_variable cv;

    std::function<void()> producer_thread_function = [&]() {
        while (true)
        {
            std::unique_lock<std::mutex> ul(mut);
            cv.wait(ul, [&]() { return buffer.size() <= 0; });

            while (buffer.size() != max_buffer_size)
            {
                p.Produce([]() {
                    uint8_t value = random_number();
                    std::cout << "Produced " << static_cast<int>(value) << std::endl;
                    return value;
                });
            }

            cv.notify_one();
        }
    };

    std::function<void()> consumer_thread_function = [&]() {
        while (true)
        {
            std::unique_lock<std::mutex> ul(mut);
            cv.wait(ul, [&]() { return buffer.size() >= max_buffer_size; });
            while (buffer.size() != 0)
            {
                c.Consume([](uint8_t value) {
                    std::cout << "Consumed " << static_cast<int>(value) << std::endl;
                });
            }

            cv.notify_one();
        }
    };

    std::thread producer_thread(producer_thread_function);
    std::thread consumer_thread(consumer_thread_function);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
