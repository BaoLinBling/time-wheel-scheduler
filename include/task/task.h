#ifndef TASK_H
#define TASK_H

#include <functional>
#include <memory>
#include <cstdint>

// 任务回调函数类型
using TaskCallback = std::function<void()>;

// 任务类
class Task {
public:
    uint64_t task_id_;         // 唯一任务ID
    uint64_t exec_ms_;        // 执行时间戳（ms）
    uint64_t interval_ms_;    // 循环间隔（0=只执行一次）
    TaskCallback cb_;         // 业务回调

public:
    Task(uint64_t id, uint64_t exec_ms, uint64_t interval, TaskCallback cb)
        : task_id_(id),
          exec_ms_(exec_ms),
          interval_ms_(interval),
          cb_(std::move(cb)) {}

    // 执行任务
    void run() {
        if (cb_) cb_();
    }

    // 是否是循环任务
    bool is_loop() const {
        return interval_ms_ > 0;
    }
};

// 智能指针别名（面试必问：C++17 智能指针）
using TaskPtr = std::shared_ptr<Task>;

#endif
