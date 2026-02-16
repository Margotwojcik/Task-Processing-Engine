#include "ThreadPool.hpp"
#include <iostream>

int main() {
    ThreadPool pool(4); // 4 wątki w puli

    for (int i = 0; i < 10; ++i) {
        pool.enqueue([i]() {
            std::cout << "Task " << i << " executed by thread "
                      << std::this_thread::get_id() << "\n";
        });
    }

    // pool destruktor czeka aż wszystkie wątki skończą
    return 0;
}
