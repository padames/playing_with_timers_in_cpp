#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include "App.h"
// TODO: implement https://stackoverflow.com/a/7105779/1585486
// TODO: undo these changes inspired by http://www.bo-yang.net/2017/11/19/cpp-kill-detached-thread
//       because cancelling is forceful and it makes difficult to delete the resources the trhead might have been using when it was stopped


App::~App()
{
    for( auto&  it: tm_ )
    {
        stop_thread(it.first);
    }
}

void App::run() 
{
    // std::cout << " will start the thread " << std::endl;
    start_thread("t1", 15);
    start_thread("t2", 20);

}

void App::start_thread(const std::string &tname, int time_out_seconds)
{
    std::thread thrd = std::thread(&App::start, this, tname, time_out_seconds);
    thrd.detach();
    tm_[tname] = thrd.native_handle();
    std::cout << "Thread " << tname << " created:" << std::endl;
}

void App::stop_thread(const std::string &tname)
{
    ThreadMap::const_iterator it = tm_.find(tname);
    if (it != tm_.end()) {
        // pthread_cancel(it->second);
        it->second;
        tm_.erase(tname);
        std::cout << "Thread " << tname << " killed:" << std::endl;
    }
}


void App::start(App* app, const std::string& tname, int tm_out_in_seconds)
{
    // std::cout << " about to run the timer " << std::endl;
    app->timer(std::chrono::seconds(tm_out_in_seconds));
}

void App::timer( std::chrono::duration<int,std::ratio<1,1>> const&  timeout_duration ) 
{
    auto const timeout= std::chrono::steady_clock::now() + \
        std::chrono::milliseconds(timeout_duration);
    {
        // std::cout << " in the timer about to lock the cv " << std::endl;
        std::unique_lock<std::mutex> lk(sync_point_);
        done_ = false;
        while(!done_)
        {
            if(cv_.wait_until(lk,timeout)==std::cv_status::timeout){
                done_ = true;
            }
        }
    }
}
