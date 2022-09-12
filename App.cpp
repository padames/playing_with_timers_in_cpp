#include <chrono>
#include <iostream>
#include "App.h"

// TODO: implement https://stackoverflow.com/a/7105779/1585486

App::~App()
{
    if (tt.joinable()) 
    {
        tt.join();
        std::cout << "Joined the thread that run the timer function in the application" << std::endl;
    }
}

void App::run() 
{
    // std::cout << " will start the thread " << std::endl;
    tt = std::thread(start, this);
}

void App::start(App* app)
{
    // std::cout << " about to run the timer " << std::endl;
    app->timer(std::chrono::seconds(15));
    return;
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