#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include "ThreadPool.hpp"

std::mutex coutMutex;

int main() {
    ThreadPool pool(4);

    std::vector<std::future<int>> results;

    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));

                {
                    std::lock_guard<std::mutex> lock(coutMutex);
                    std::cout << "Processing task "
                              << i
                              << " on thread "
                              << std::this_thread::get_id()
                              << std::endl;
                }

                return i * i;
            })
        );
    }

    std::cout << "\nResults:\n";

    for (auto && result : results)
        std::cout << result.get() << std::endl;

    return 0;
}