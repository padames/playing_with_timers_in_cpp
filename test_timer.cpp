#include "App.h"
#include "Timer.h"
#include "ManagedTimer.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>


class App;
ManagedTimer* t1;
ManagedTimer* t2;

void handleInterrupt(int signum)
{
    std::cout << " Caught interrupt signal (ctr+C), stopping timers." << std::endl;
    t1->stop();
    t2->stop();
    exit(0);
}

int main() {

    
    
    App the_app{};

    the_app.run();

    // Timer timer{5000, [&]() { std::cout<< "done!!" << std::endl;}};
    std::unique_ptr timer1 = std::make_unique<ManagedTimer>([&]() { std::cout<< "First ManagedTimer done!!" << std::endl;});
    ManagedTimer timer2{[&](){ std::cout<< "second ManagedTimer done!!" << std::endl;}};
    t1=timer1.get();
    t2=&timer2;

    signal(SIGINT, handleInterrupt);
    timer1->start(5000);
    timer2.start(2000);

    std::cout << " waiting for the timer to expire (s): ";

    int count = 0;
    while(the_app.isRunning())
    {
        std::cout << "Main loop: " << ++count << std::endl; 
        std::cout.flush(); 
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (count == 3) {
            timer1->stop();
        }
        if (count == 4) {
            timer1->start(3000);
            // timer2.start(1000);
        }
    }
    std::cout << std::endl;    
    timer1->stop();
    timer2.stop();    
    timer1->start(4000);
    timer1->stop();
    timer2.stop();
    
    return 0;
}