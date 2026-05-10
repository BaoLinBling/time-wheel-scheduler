# time-wheel-scheduler

A hierarchical time wheel based high-performance delay task scheduler implemented in C++17.

## Features
- Three-level hierarchical time wheel (seconds/minutes/hours) for O(1) task scheduling
- Independent background scheduling thread, non-blocking to main business logic
- Thread-safe design with mutex locks and atomic operations
- Supports delay tasks, easy to extend for periodic tasks and task cancellation
- Lightweight architecture, zero third-party dependencies, easy to integrate

## Build & Run
```bash
./build.sh
cd bin
./time_wheel_demo
