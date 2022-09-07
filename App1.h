#ifndef APP_H
#define APP_H
#include <mutex>


class App {

public:
    App() : done_(false) {}
    void run();

private:
    std::mutex sync_point;
    bool done_;
};

#endif