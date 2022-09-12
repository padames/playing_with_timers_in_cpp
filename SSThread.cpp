#include <functional>
#include <chrono>

#include "Cancellation.h"
#include "SSThread.h"

void SSThread::start() {
        thread_ = std::unique_ptr<std::thread>(
            new std::thread(std::bind(&SSThread::run, this)));
    }


void SSThread::stop() {
    cpoint_.cancel();
    thread_->join();
}


void SSThread::run() {
    std::cout << "thread started\n";
    try {
        while (true) {
            cpoint_.wait(std::chrono::seconds(1));
        }
    } catch (const cancelled_error&) {
        std::cout << "thread cancelled\n";
    }
}

