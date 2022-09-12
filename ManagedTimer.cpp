#include <memory>
#include "ManagedTimer.h"



ManagedTimer::ManagedTimer(size_t time, const std::function<void(void)>& f) 
    : is_running_{false}, time_{std::chrono::milliseconds{time}}, f_{f} 
{}

void ManagedTimer::start() 
{
    if (!is_running_)
    {
        wait_thread_ = std::unique_ptr<std::thread>(
            new std::thread(std::bind(&ManagedTimer::run, this)));
    }
    else
    {
        std::cout << "MangedTimer ran already" << std::endl;
    }
}

void ManagedTimer::stop() 
{
    cpoint_.cancel();
    if (wait_thread_->joinable())
    {
        auto id = wait_thread_->get_id();
        wait_thread_->join(); 
        std::cout << "Joined the ManagedTimer " << id << std::endl;
    }
}

void ManagedTimer::run() 
{
    if (!is_running_)
        is_running_ = true;

    std::cout << "thread started\n";
    try {
        std::unique_lock<std::mutex> lck{mtx_};
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time_).count();
        std::cout << "ManagedTimer time count in seconds " << seconds << std::endl;
        for(int i{10}; i > 0; --i) {
            std::cout << "Thread " << wait_thread_->get_id() << " countdown at: " << '\t' << i << '\n';
            cpoint_.wait(1);
        }
        f_();
    } catch (const cancelled_error&) {
        std::cout << "thread cancelled\n";
    }
}
