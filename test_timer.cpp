#include "App.h"
#include "Timer.h"
#include <iostream>
#include <thread>
#include <chrono>


class App;

int main() {

    App the_app{};

    the_app.run();

    Timer timer{5000, [&]() { std::cout<< "done!!" << std::endl;}};


    std::cout << " waiting for the timer to expire (s): ";

    int count = 1;
    while(the_app.isRunning())
    {
        std::cout << count << " "; 
        std::cout.flush(); 
        count++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl;    
    return 0;
}