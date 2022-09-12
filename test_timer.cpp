#include "App.h"
#include "Timer.h"
#include "ManagedTimer.h"
#include <iostream>
#include <thread>
#include <chrono>


class App;

int main() {

    App the_app{};

    the_app.run();

    // Timer timer{5000, [&]() { std::cout<< "done!!" << std::endl;}};
    ManagedTimer timer{5000, [&]() { std::cout<< "done!!" << std::endl;}};

    timer.start();
    
    std::cout << " waiting for the timer to expire (s): ";

    int count = 0;
    while(the_app.isRunning())
    {
        std::cout << "Main loop: " << count++ << std::endl; 
        std::cout.flush(); 
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl;    
    timer.stop();
    return 0;
}