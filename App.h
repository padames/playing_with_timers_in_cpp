#ifndef APP_H
#define APP_H
#include <mutex>
#include <condition_variable>
#include <thread>


class App {

public:
    App() : done_(false) {}
    ~App();
    void run();
    static void start(App* app);
    void timer( std::chrono::duration<int,std::ratio<1,1>> const& timeout_duration); 
    bool isRunning() const { return !done_; }

private:
    std::condition_variable cv_;
    mutable std::mutex sync_point_;
    bool done_;
    std::thread tt;
};

#endif