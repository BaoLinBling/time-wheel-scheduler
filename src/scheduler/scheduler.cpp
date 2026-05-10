#include "scheduler/scheduler.h"
#include "common/time_util.h"
#include <stdexcept>

static uint64_t g_task_id = 1;

Scheduler::Scheduler() : running_(false) {}

Scheduler::~Scheduler() {
    stop();
}

void Scheduler::start() {
    if (running_) return;
    running_ = true;
    thread_ = std::thread(&Scheduler::run_loop, this);
}

void Scheduler::stop() {
    if (!running_) return;
    running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
}

uint64_t Scheduler::add_delay_task(uint64_t delay_ms, TaskCallback cb) {
    std::lock_guard<std::mutex> lock(mutex_);
    uint64_t now = GetCurrentMs();
    uint64_t exec_ms = now + delay_ms;
    auto task = std::make_shared<Task>(g_task_id++, exec_ms, 0, std::move(cb));
    wheel_.add_task(task);
    return task->task_id_;
}

void Scheduler::run_loop() {
    while (running_) {
        std::lock_guard<std::mutex> lock(mutex_);
        wheel_.tick();             // 旧：step() → 新：tick()
        auto tasks = wheel_.get_expired(); // 旧：get_expired_tasks → 新：get_expired()
        for (auto& t : tasks) {
            t->run();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}