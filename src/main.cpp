#include <iostream>
#include "scheduler/scheduler.h"

int main() {
    std::cout << "==== C++17 Time Wheel Scheduler ====" << std::endl;

    // 创建调度器
    Scheduler scheduler;

    // 启动后台线程
    scheduler.start();
    std::cout << "调度器启动成功（独立线程运行）" << std::endl;

    // 添加 2秒 任务
    scheduler.add_delay_task(2000, []() {
        std::cout << "[2s] 任务执行" << std::endl;
    });

    // 添加 5秒 任务
    scheduler.add_delay_task(5000, []() {
        std::cout << "[5s] 任务执行" << std::endl;
    });

    // 主线程等待
    std::cout << "按回车键退出..." << std::endl;
    std::cin.get();

    // 停止
    scheduler.stop();
    std::cout << "调度器已停止" << std::endl;

    return 0;
}