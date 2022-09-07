#ifndef APP_H
#define APP_H
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unordered_map>


class App {

public:
    App() : done_(false) {}
    ~App();
    void run();
    static void start(App* app, const std::string& tname, int tm_out_in_seconds);
    void start_thread(const std::string &tname, int time_out_seconds);
    void stop_thread(const std::string &tname);
    void timer( std::chrono::duration<int,std::ratio<1,1>> const& timeout_duration); 
    bool isRunning() const { return !done_; }

private:
    std::condition_variable cv_;
    mutable std::mutex sync_point_;
    bool done_;
    
    typedef std::unordered_map<std::string, std::thread::native_handle_type> ThreadMap;
    ThreadMap tm_;    
};

#endif