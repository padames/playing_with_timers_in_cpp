#ifndef CANCELLATION_H
#define CANCELLATION_H

#include <mutex>
#include <condition_variable>
#include <atomic>

struct cancelled_error {};

class Cancellation
{
public:
    Cancellation();

    void cancel();
    void reset(); 

    void wait(int seconds);
private:
    std::atomic<bool> stop_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif