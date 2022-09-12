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
    ManagedTimer timer1{5000, [&]() { std::cout<< "First ManagedTimer done!!" << std::endl;}};
    ManagedTimer timer2{2000, [&](){ std::cout<< "second ManagedTimer done!!" << std::endl;}};

    timer1.start();
    timer2.start();

    std::cout << " waiting for the timer to expire (s): ";

    int count = 0;
    while(the_app.isRunning())
    {
        std::cout << "Main loop: " << count++ << std::endl; 
        std::cout.flush(); 
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (count == 3) {
            timer1.stop();
        }
    }
    std::cout << std::endl;    
    timer1.stop();
    timer2.stop();    
    timer1.start();

    return 0;
}