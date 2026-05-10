#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include <chrono>
#include <cstdint>

inline uint64_t GetCurrentMs()
{
    auto now = std::chrono::system_clock::now();
    auto dura = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(dura).count();
}

#endif
