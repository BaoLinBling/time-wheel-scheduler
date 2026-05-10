#include "time_wheel/time_wheel.h"
#include "common/time_util.h"

HierarchicalTimeWheel::HierarchicalTimeWheel() {
    second_wheel_.resize(WHEEL_SLOT);
    minute_wheel_.resize(WHEEL_SLOT);
    hour_wheel_.resize(24);
    current_ms_ = GetCurrentMs();
}

void HierarchicalTimeWheel::tick() {
    current_ms_ += MS_PER_TICK;

    uint64_t sec = (current_ms_ / 1000) % 60;
    if (sec == 0) {
        cascade(minute_wheel_, 1);
        uint64_t min = (current_ms_ / 1000 / 60) % 60;
        if (min == 0) {
            cascade(hour_wheel_, 2);
        }
    }
}

void HierarchicalTimeWheel::add_task(const TaskPtr& task) {
    uint64_t diff_ms = task->exec_ms_ - current_ms_;
    if (diff_ms < 0) diff_ms = 0;

    uint64_t sec = diff_ms / 1000;
    if (sec < 60) {
        second_wheel_[sec % WHEEL_SLOT].push_back(task);
    } else if (sec < 3600) {
        minute_wheel_[(sec / 60) % WHEEL_SLOT].push_back(task);
    } else {
        hour_wheel_[(sec / 3600) % 24].push_back(task);
    }
}

std::list<TaskPtr> HierarchicalTimeWheel::get_expired() {
    uint64_t sec = (current_ms_ / 1000) % 60;
    std::list<TaskPtr> tasks;
    tasks.swap(second_wheel_[sec]);
    return tasks;
}

void HierarchicalTimeWheel::cascade(std::vector<std::list<TaskPtr>>& from_wheel, int level) {
    for (auto& slot : from_wheel) {
        for (auto& task : slot) {
            add_task(task);
        }
        slot.clear();
    }
}
