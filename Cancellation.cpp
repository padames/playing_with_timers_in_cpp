#include <functional>
#include <condition_variable>
#include <mutex>

#include "Cancellation.h"

Cancellation::Cancellation() : stop_(false) {}

void Cancellation::cancel()
{
    std::unique_lock<std::mutex> lock(mutex_);
    stop_ = true;
    cond_.notify_all();
}

void Cancellation::reset()
{
    std::unique_lock<std::mutex> lock(mutex_);
    stop_=false;
}


void Cancellation::wait(int seconds) 
{
    std::unique_lock<std::mutex> lock(mutex_);
    auto t = std::chrono::seconds(seconds);
    if (stop_ || cond_.wait_for(lock, t) == std::cv_status::no_timeout) {
        stop_ = false;
        throw cancelled_error();
    }
}
