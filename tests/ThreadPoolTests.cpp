#include <gtest/gtest.h>

#include "ThreadPool.hpp"

TEST(ThreadPoolTest, ExecutesTask)
{
    ThreadPool pool(2);

    auto result = pool.enqueue([] {
        return 42;
    });

    EXPECT_EQ(result.get(), 42);
}