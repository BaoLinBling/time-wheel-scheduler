#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
#include "time_wheel/time_wheel.h"
#include "task/task.h"

class Scheduler {
private:
    TimeWheel wheel_;          // 时间轮
    std::thread thread_;       // 调度线程
    std::atomic<bool> running_;// 运行标志
    std::mutex mutex_;         // 线程安全锁

public:
    Scheduler();
    ~Scheduler();

    // 启动调度器
    void start();

    // 停止调度器
    void stop();

    // 添加延时任务（毫秒）
    uint64_t add_delay_task(uint64_t delay_ms, TaskCallback cb);

private:
    // 后台调度循环
    void run_loop();
};

#endif
