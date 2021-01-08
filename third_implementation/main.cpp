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

#include <third_implementation/pch.h>
#include <config.h>

#include <third_implementation/base.hpp>
#include <third_implementation/producer.hpp>
#include <third_implementation/consumer.hpp>

#include <CLI11.hpp>

int main(int argc, char **argv)
{
    /* Initialize CLI */
    CLI::App app{"Producer Consumer - Third Implementation"};

    /* User args */
    uint8_t producers_count = 5;
    uint8_t consumers_count = 5;

    /* CLI options */
    app.add_option("-p,--producers", producers_count, "Number of producers")->required()->check(CLI::Range(1, 255));
    app.add_option("-c,--consumers", consumers_count, "Number of consumers")->required()->check(CLI::Range(1, 255));

    /* Parse CLI args */
    CLI11_PARSE(app, argc, argv);

    /* Initialize Logger */
    Horus::Logger::Init();

    /* CMake Configured File Defines */
    H_INFO("PROJECT NAME => {}", "Producer Consumer - Third Implementation");
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
            cv.wait(ul, [&]() { return buffer.size() < max_buffer_size; });

            p.Produce([]() {
                uint8_t value = random_number();
                using namespace std::literals;
                std::this_thread::sleep_for(200ms);
                std::cout << "T[" << std::this_thread::get_id() << "] Produced " << static_cast<int>(value) << std::endl;
                return value;
            });

            cv.notify_all();
        }
    };

    std::function<void()> consumer_thread_function = [&]() {
        while (true)
        {
            std::unique_lock<std::mutex> ul(mut);
            cv.wait(ul, [&]() { return buffer.size() > 0; });

            c.Consume([](uint8_t value) {
                using namespace std::literals;
                std::this_thread::sleep_for(200ms);
                std::cout << "T[" << std::this_thread::get_id() << "] Consumed " << static_cast<int>(value) << std::endl;
            });

            cv.notify_all();
        }
    };

    std::vector<std::thread> producer_thread_pool;
    std::vector<std::thread> consumer_thread_pool;

    /* Creating producer thread pool */
    for (size_t i = 0; i < producers_count; i++)
        producer_thread_pool.push_back(std::thread(producer_thread_function));

    /* Creating consumer thread pool */
    for (size_t i = 0; i < consumers_count; i++)
        consumer_thread_pool.push_back(std::thread(consumer_thread_function));

    /* Joining producer thread pool */
    for (size_t i = 0; i < producers_count; i++)
        producer_thread_pool[i].join();

    /* Joining consumer thread pool */
    for (size_t i = 0; i < consumers_count; i++)
        consumer_thread_pool[i].join();

    return 0;
}
