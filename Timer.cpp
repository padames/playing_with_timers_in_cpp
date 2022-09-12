#include "Timer.h"


Timer::Timer(size_t time, const std::function<void(void)>& f) 
    : time_{std::chrono::milliseconds{time}}, f_{f} 
    {
        wait_thread_ = std::thread{[&]() {wait_then_call(); }};
    }

Timer::~Timer() 
{ 
    if (wait_thread_.joinable())
    {
        wait_thread_.join(); 
        std::cout << "Joined the Timer object in its destructor!" << std::endl;
    }

}

void Timer::wait_then_call()
{
    std::unique_lock<std::mutex> lck{mtx_};
    for(int i{10}; i > 0; --i) {
        std::cout << "Thread " << wait_thread_.get_id() << " countdown at: " << '\t' << i << '\n';
        cv_.wait_for(lck, time_ / 10);
    }
    f_();
}