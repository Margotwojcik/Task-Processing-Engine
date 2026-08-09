# Task Processing Engine — C++ Thread Pool

A lightweight task processing engine implemented in **modern C++17**. The project provides a fixed-size thread pool for executing tasks concurrently using worker threads and a thread-safe task queue.

The project focuses on **multithreading, synchronization, RAII, asynchronous task execution, automated testing, and modern C++ practices**.

## Features

* Fixed-size thread pool with configurable number of worker threads
* Thread-safe task queue
* Concurrent task execution using `std::thread`
* Task synchronization using:

  * `std::mutex`
  * `std::condition_variable`
* Asynchronous results using `std::future`
* Task execution using `std::packaged_task`
* Graceful shutdown and worker synchronization
* Exception propagation through `std::future`
* RAII-based resource management
* C++17 implementation
* CMake build system
* Automated unit tests using GoogleTest
* No external runtime dependencies

## Architecture

The Thread Pool consists of three main components:

```text
                +-------------------+
                |    ThreadPool     |
                +---------+---------+
                          |
                          v
                +-------------------+
                |   Task Queue      |
                | std::queue        |
                +---------+---------+
                          |
              +-----------+-----------+
              |           |           |
              v           v           v
          Worker 1    Worker 2    Worker 3 ... Worker N
              |           |           |
              +-----------+-----------+
                          |
                          v
                     Execute Task
```

When a task is submitted, it is placed in a synchronized queue. Worker threads wait for available tasks using `std::condition_variable`.

When a task becomes available:

1. A worker thread wakes up.
2. The worker safely removes a task from the queue.
3. The queue lock is released.
4. The task is executed.
5. The result is returned through `std::future`.

This allows multiple tasks to be processed concurrently without creating a new thread for every task.

## Technologies

* **C++17**
* STL
* `std::thread`
* `std::mutex`
* `std::condition_variable`
* `std::future`
* `std::packaged_task`
* CMake
* GoogleTest
* Git / GitHub

## Project Structure

```text
Task-Processing-Engine-Modern-Cpp-Thread-Pool/
│
├── include/
│   └── ThreadPool.hpp
│
├── src/
│   └── ThreadPool.cpp
│
├── examples/
│   └── main.cpp
│
├── tests/
│   └── ThreadPoolTests.cpp
│
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Building

### Requirements

* C++17 compatible compiler
* CMake 3.20+
* Git

### Configure the project

From the project root:

```bash
mkdir build
cd build
cmake ..
```

### Build

```bash
cmake --build . --config Release
```

On Windows with Visual Studio, the executable will be generated in:

```text
build/Release/
```

## Running the Example

After building, run:

```text
TaskProcessingEngine.exe
```

Example output:

```text
Results:
Processing task 3 on thread 18392
Processing task 2 on thread 12520
Processing task 1 on thread 18072
Processing task 0 on thread 23260
0
1
4
9
Processing task 6 on thread 18072
Processing task 7 on thread 23260
Processing task 5 on thread 12520
Processing task 4 on thread 18392
16
25
36
49
```

The different thread IDs demonstrate that tasks are distributed between multiple worker threads.

## Testing

The project uses **GoogleTest** for automated testing.

Build the project first:

```bash
cmake --build . --config Release
```

Then run:

```bash
ctest -C Release --output-on-failure
```

The test suite currently verifies:

* Basic task execution
* Correct task results
* Execution of multiple tasks
* Concurrent task execution
* Different return types
* Exception propagation
* Rejection of tasks after shutdown

All tests currently pass successfully.

## Example Usage

```cpp
ThreadPool pool(4);

auto result = pool.enqueue([] {
    return 42;
});

std::cout << result.get() << std::endl;
```

Output:

```text
42
```

Multiple tasks can also be submitted:

```cpp
for (int i = 0; i < 8; ++i)
{
    pool.enqueue([i] {
        return i * i;
    });
}
```

The tasks are distributed between the available worker threads.

## Design Decisions

### Fixed-size worker pool

A fixed number of worker threads avoids creating and destroying a thread for every individual task.

### Condition variable

Workers sleep while there are no tasks available instead of continuously polling the queue.

### Mutex

Access to the shared task queue is synchronized using `std::mutex` to prevent data races.

### Futures

`std::future` allows the caller to retrieve asynchronous task results and receive exceptions thrown during task execution.

### RAII

The Thread Pool automatically shuts down its worker threads when the object is destroyed, ensuring that resources are properly released.

## Testing Strategy

The project tests both normal and exceptional execution paths.

Examples include:

```text
Task execution
      ↓
Correct result
      ↓
Concurrent execution
      ↓
Exception propagation
      ↓
Shutdown behaviour
```

This helps verify not only the functionality of the Thread Pool but also its behaviour under error conditions.

## Possible Future Improvements

* Dynamic worker thread management
* Task priorities
* Cancellation support
* Task timeouts
* Performance benchmarks
* Work-stealing queue
* Improved task scheduling
* Linux/Unix-specific testing
* Additional stress tests

## What I Learned

This project helped me develop practical understanding of:

* Modern C++ concurrency
* Thread synchronization
* Producer-consumer patterns
* RAII and resource management
* Asynchronous programming with futures
* STL concurrency utilities
* CMake-based project organization
* Automated testing with GoogleTest
* Debugging multithreaded applications

## License

This project is available for educational and portfolio purposes.
