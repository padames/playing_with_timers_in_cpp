#include <memory>
#include "ManagedTimer.h"



ManagedTimer::ManagedTimer(size_t time, const std::function<void(void)>& f) 
    : is_running_{false}, time_{std::chrono::milliseconds{time}}, f_{f} 
{}

void ManagedTimer::start() 
{
    // if (wait_thread_->joinable()) {
    //     if (!is_running_)
    //     {
    //         std::cout << "starting " << std::endl;
    //         wait_thread_ = std::unique_ptr<std::thread>(
    //             new std::thread(std::bind(&ManagedTimer::run, this)));
    //     }
    //     else
    //     {
    //         std::cout << "MangedTimer already running at " << wait_thread_->get_id() << std::endl;
    //     }
    // }
    // else
    // {
    //     std::cout << "MangedTimer is stopped " << std::endl;
    // }

    if (is_running_)
    {
        std::cout << "MangedTimer already running at " << wait_thread_->get_id() << std::endl;
    }
    else
    {
        std::cout << "starting " << std::endl;
        if (!wait_thread_)
        {
            wait_thread_.reset(new std::thread(std::bind(&ManagedTimer::run, this)));
            std::cout << "Resetting the null thread pointer" << std::endl;
        }
        else
        {
            wait_thread_ = std::unique_ptr<std::thread>(new std::thread(std::bind(&ManagedTimer::run, this)));
            std::cout << "making a new thread pointer" << std::endl;
        }
    }
}

void ManagedTimer::stop() 
{
    { 
        std::lock_guard<std::mutex> lk(mtx_);
        if(is_running_)
            cpoint_.cancel();
    }
    
    std::cout << " Stopping..." << std::endl;
    if (wait_thread_)
    {
        auto id = wait_thread_->get_id();
        wait_thread_->join(); 
        std::cout << "ManagedTimer thread " << id << " was joined!" << std::endl;
        wait_thread_.release();
        std::cout << "In Stop() after release " << std::boolalpha << (wait_thread_? true:false) << std::endl;
        
        {   
            std::lock_guard<std::mutex> lk(mtx_);
            is_running_ = false;
        }
    }
    else
    {
        std::cout << "Already stopped!" << std::endl;
    }
}

void ManagedTimer::run() 
{
    if (!is_running_)
        is_running_ = true;

    std::cout << "thread started\n";
    try {
        std::unique_lock<std::mutex> lck{mtx_};
        // auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time_).count();
        auto seconds = time_.count()/1000;
        std::cout << "ManagedTimer time count in seconds " << seconds << std::endl;
        for(long int i{seconds}; i > 0; --i) {
            std::cout << "Thread " << wait_thread_->get_id() << " countdown at: " << '\t' << i << '\n';
            cpoint_.wait(1);
        }
        f_();
    } catch (const cancelled_error&) {
        std::cout << "thread cancelled, will stop\n";
    }
}
