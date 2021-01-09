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
            /* Getting thread id */
            std::stringstream ss;
            ss << std::this_thread::get_id();
            std::string thread_id = ss.str();

            /* lock */
            H_DEBUG("Producer#{} waiting", thread_id);
            sem.wait();

            /**
             * @brief Produce until buffer is full
             *
             */
            while (buffer.size() != max_buffer_size)
            {
                H_DEBUG("Producer#{} started", thread_id);

                /* Generating random runber */
                H_DEBUG("Producer#{} generating random value", thread_id);
                uint8_t value = random_number();

                /* Sending to buffer */
                H_DEBUG("Producer#{} sending value to buffer", thread_id);
                buffer.push_back(value);

                std::cout << "Thread#" << thread_id << " Produced " << static_cast<int>(value) << std::endl;

                /* Sleep for 200 miliseconds */
                H_DEBUG("Producer#{} sleeping", thread_id);
                using namespace std::literals;
                std::this_thread::sleep_for(200ms);
            }

            /* Release */
            H_DEBUG("Producer#{} notify", thread_id);
            sem.notify();
        }
    };

    /*Consumer function */
    std::function<void()> consumer = [&]() {
        while (true)
        {
            /* Getting thread id */
            std::stringstream ss;
            ss << std::this_thread::get_id();
            std::string thread_id = ss.str();

            /* Lock */
            H_DEBUG("Consumer#{} waiting", thread_id);
            sem.wait();

            /**
             * @brief Consume until buffe is empty
             *
             */
            while (buffer.size() != 0)
            {

                H_DEBUG("Producer#{} started", thread_id);

                /* Getting the next buffered value */
                H_DEBUG("Consumer#{} getting next buffered value", thread_id);
                uint8_t value = buffer.front();

                /* Removing from buffer */
                H_DEBUG("Consumer#{} removing consumed value from buffer", thread_id);
                buffer.pop_front();

                std::cout << "Thread#" << thread_id << " Consumed " << static_cast<int>(value) << std::endl;

                /* Sleep for 200 miliseconds */
                H_DEBUG("Consumer#{} sleeping", thread_id);
                using namespace std::literals;
                std::this_thread::sleep_for(200ms);
            }

            /* Release */
            H_DEBUG("Consumer#{} notify", thread_id);
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
