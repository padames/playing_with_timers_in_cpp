#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include "App.h"

void App::run() 
{
    this->done_=false;
    
    std::thread tt([&]() {
            if (this->done_) return 0;
            std::cout << "about to sleep in thread" << std::endl;
            std::this_thread::sleep_for( std::chrono::seconds(30));
            this->done_=true;
            std::cout << "set done to true in thread" << std::endl;
            return 0;          
        });
    tt.detach();
    std::cout << "waiting ";
    while(true)
    {
        std::cout << ".";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if  (done_) break;
    }
}
