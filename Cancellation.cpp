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

template <typename P>
void Cancellation::wait(const P& period) 
{
    std::unique_lock<std::mutex> lock(mutex_);
    if (stop_ || cond_.wait_for(lock, period) == std::cv_status::no_timeout) {
        stop_ = false;
        throw cancelled_error();
    }
}
