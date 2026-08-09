#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

#include "ThreadPool.hpp"


TEST(ThreadPoolTest, ExecutesTask)
{
    ThreadPool pool(2);

    auto result = pool.enqueue([] {
        return 42;
    });

    EXPECT_EQ(result.get(), 42);
}


TEST(ThreadPoolTest, ReturnsCorrectResult)
{
    ThreadPool pool(2);

    auto result = pool.enqueue([] {
        return 10 + 20;
    });

    EXPECT_EQ(result.get(), 30);
}


TEST(ThreadPoolTest, ExecutesMultipleTasks)
{
    ThreadPool pool(4);

    std::vector<std::future<int>> results;

    for (int i = 0; i < 100; ++i)
    {
        results.push_back(
            pool.enqueue([i] {
                return i * i;
            })
        );
    }

    for (int i = 0; i < 100; ++i)
    {
        EXPECT_EQ(results[i].get(), i * i);
    }
}


TEST(ThreadPoolTest, ExecutesTasksConcurrently)
{
    ThreadPool pool(4);

    std::atomic<int> completedTasks{0};

    std::vector<std::future<void>> results;

    for (int i = 0; i < 4; ++i)
    {
        results.push_back(
            pool.enqueue([&completedTasks] {
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(100)
                );

                ++completedTasks;
            })
        );
    }

    for (auto& result : results)
    {
        result.get();
    }

    EXPECT_EQ(completedTasks.load(), 4);
}


TEST(ThreadPoolTest, HandlesDifferentReturnTypes)
{
    ThreadPool pool(2);

    auto intResult = pool.enqueue([] {
        return 123;
    });

    auto stringResult = pool.enqueue([] {
        return std::string("ThreadPool");
    });

    EXPECT_EQ(intResult.get(), 123);
    EXPECT_EQ(stringResult.get(), "ThreadPool");
}



TEST(ThreadPoolTest, HandlesTaskExceptions)
{
    ThreadPool pool(2);

    auto result = pool.enqueue([]() -> int {
        throw std::runtime_error("Task failed");
    });

    EXPECT_THROW(result.get(), std::runtime_error);
}


TEST(ThreadPoolTest, RejectsTasksAfterShutdown)
{
    ThreadPool pool(2);

    pool.shutdown();

    EXPECT_THROW(
        pool.enqueue([] {
            return 42;
        }),
        std::runtime_error
    );
}