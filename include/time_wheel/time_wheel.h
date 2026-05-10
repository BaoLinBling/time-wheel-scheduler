#ifndef TIME_WHEEL_H
#define TIME_WHEEL_H

#include <vector>
#include <list>
#include <memory>
#include <cstdint>
#include "task/task.h"

// 分层时间轮：秒(60)、分(60)、时(24)
constexpr uint32_t WHEEL_SLOT = 60;
constexpr uint32_t MS_PER_TICK = 1000;

class HierarchicalTimeWheel {
private:
    // 每一层轮盘
    std::vector<std::list<TaskPtr>> second_wheel_;
    std::vector<std::list<TaskPtr>> minute_wheel_;
    std::vector<std::list<TaskPtr>> hour_wheel_;

    uint64_t current_ms_;

public:
    HierarchicalTimeWheel();

    // 推进1个tick（1秒）
    void tick();

    // 添加任务
    void add_task(const TaskPtr& task);

    // 获取所有到期任务
    std::list<TaskPtr> get_expired();

private:
    // 任务降级（从上层往下层翻）
    void cascade(std::vector<std::list<TaskPtr>>& from_wheel, int level);
};

// 别名，方便使用
using TimeWheel = HierarchicalTimeWheel;

#endif
