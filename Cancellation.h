#ifndef CANCELLATION_H
#define CANCELLATION_H

#include <mutex>
#include <condition_variable>

struct cancelled_error {};

class Cancellation
{
public:
    Cancellation();

    void cancel(); 

    template <typename P>
    void wait(const P& period);
private:
    bool stop_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif