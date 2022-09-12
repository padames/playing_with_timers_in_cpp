#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

// From https://stackoverflow.com/a/41152829/1585486


class Timer {
public:
    Timer(size_t time, const std::function<void(void)>& f);
    virtual ~Timer();

private:
    void wait_then_call();
    std::mutex mtx_;
    std::condition_variable cv_{};
    std::chrono::milliseconds time_;
    std::function <void(void)> f_;
    std::thread wait_thread_;
};
#endif