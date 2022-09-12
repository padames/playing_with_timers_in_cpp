#ifndef MANAGEDTIMER_H
#define MANAGEDTIMER_H

#include <thread>
#include <functional>
#include <iostream>
#include "Cancellation.h"

class Cancellation;

class ManagedTimer
{
public:
    ManagedTimer(size_t time, const std::function<void(void)>& f);
    void start();
    void stop();
private:
    void run();
    std::unique_ptr<std::thread> wait_thread_;
    Cancellation cpoint_;
    std::mutex mtx_;
    std::condition_variable cv_{};
    std::chrono::milliseconds time_;
    std::function <void(void)> f_;
};
#endif