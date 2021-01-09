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

#include <third_implementation/helpers.hpp>

/* Cli args utility */
#include <CLI11.hpp>

int main(int argc, char **argv)
{
    /* Initialize CLI */
    CLI::App app{"Producer Consumer - Third Implementation"};

    /* User args */
    uint8_t producers_count = 5;
    uint8_t consumers_count = 5;
    uint8_t max_buffer_size = 10;

    /* CLI options */
    app.add_option("-p,--producers", producers_count, "Number of producers")->required()->check(CLI::Range(1, 20));
    app.add_option("-c,--consumers", consumers_count, "Number of consumers")->required()->check(CLI::Range(1, 20));
    app.add_option("-b,--buffer", max_buffer_size, "Maximun buffer size")->check(CLI::Range(1, 20));

    /* Parse CLI args */
    CLI11_PARSE(app, argc, argv);

    /* Initialize Logger */
    Horus::Logger::Init();

    /* CMake Configured File Defines */
    H_INFO("PROJECT NAME => {}", "Producer Consumer - Third Implementation");
    H_INFO("PROJECT VERSION => {}", PROJECT_VERSION);

    /* Application buffer */
    std::deque<uint8_t> buffer;

    /* Thread synt utils */
    std::mutex mut;
    std::condition_variable cv;

    /* Producer thread function */
    std::function<void()> producer = [&]() {
        while (true)
        {
            /* Lock and wait until has space to produce */
            std::unique_lock<std::mutex> ul(mut);
            cv.wait(ul, [&]() { return buffer.size() < max_buffer_size; });

            /* Produce the data */
            uint8_t value = random_number();

            /* Store in buffer */
            buffer.push_back(value);

            std::cout << "T[" << std::this_thread::get_id() << "] Produced " << static_cast<int>(value) << std::endl;

            /* Notify and release */
            cv.notify_all();

            /* Sleep for 200 miliseconds */
            using namespace std::literals;
            std::this_thread::sleep_for(200ms);
        }
    };

    /* Consumer thread function */
    std::function<void()> consumer = [&]() {
        while (true)
        {
            /* Lcok and wait until has data to consume */
            std::unique_lock<std::mutex> ul(mut);
            cv.wait(ul, [&]() { return buffer.size() > 0; });

            /* Consumes data */
            uint8_t value = buffer.front();

            /* Remove from buffer */
            buffer.pop_front();

            std::cout << "T[" << std::this_thread::get_id() << "] Consumed " << static_cast<int>(value) << std::endl;

            /* Notify and release */
            cv.notify_all();

            /* Sleep for 200 miliseconds */
            using namespace std::literals;
            std::this_thread::sleep_for(200ms);
        }
    };

    /* Application thread pools */
    std::vector<std::thread> producer_thread_pool;
    std::vector<std::thread> consumer_thread_pool;

    /* Creating producer thread pool */
    for (size_t i = 0; i < producers_count; i++)
        producer_thread_pool.push_back(std::thread(producer));

    /* Creating consumer thread pool */
    for (size_t i = 0; i < consumers_count; i++)
        consumer_thread_pool.push_back(std::thread(consumer));

    /* Joining producer thread pool */
    for (size_t i = 0; i < producers_count; i++)
        producer_thread_pool[i].join();

    /* Joining consumer thread pool */
    for (size_t i = 0; i < consumers_count; i++)
        consumer_thread_pool[i].join();

    return 0;
}
