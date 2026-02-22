# Task Processing Engine (Thread Pool) – C++17

A lightweight task processing engine built with modern C++ (C++17).  
This project implements a fixed-size thread pool responsible for efficient parallel task execution.

---

## What is Task Processing Engine?

Task Processing Engine is a system responsible for:

- managing worker threads
- distributing tasks between them
- executing tasks concurrently
- handling synchronization safely

Instead of creating a new thread per task (which is expensive),
the engine reuses a fixed number of worker threads.

This is a common architectural component used in:

- backend systems
- game engines
- job schedulers
- data processing pipelines
- real-time systems

---

## Core Features

- Fixed-size worker thread pool
- Thread-safe task queue
- Synchronization using:
  - `std::mutex`
  - `std::condition_variable`
- Graceful shutdown mechanism
- RAII-based resource management
- Modern C++ (C++17)
- No external dependencies

---

