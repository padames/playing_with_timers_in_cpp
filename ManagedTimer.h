#ifndef MANAGEDTIMER_H
#define MANAGEDTIMER_H

#include <thread>
#include <functional>
#include <iostream>
#include <atomic>

#include "Cancellation.h"

class Cancellation;

class ManagedTimer
{
public:
    ManagedTimer(const std::function<void(void)>& f);
    void start(size_t time);
    void stop();
    virtual ~ManagedTimer();
protected:
    virtual void run();
    /// @brief shuts down gracefully if ctr+C is received
    /// @param signum 
    void handleInterrupt(int signum);
    /// @brief to prevent false starts after is being stopped
    std::atomic<bool> is_running_;
    std::unique_ptr<std::thread> wait_thread_;
    Cancellation cpoint_{};
    std::mutex mtx_;
    std::condition_variable cv_{};
    /// @brief time to run the timer for
    std::chrono::milliseconds time_{};
    std::function <void(void)> f_;
};
#endif