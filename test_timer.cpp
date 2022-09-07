#include "App.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include "clear.h"

class App;

int main() {

    App the_app{};

    the_app.run();

    std::cout << " waiting for the timer to expire (s): ";

    int count = 1;
    while(the_app.isRunning())
    {
        // std::cout << "\x1B[2J\x1B[H";
        // std::cout<< u8"\033[2J\033[1;1H"; 
        // ClearScreen();
        std::cout << count << " "; 
        std::cout.flush(); 
        count++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl;

    return 0;
}