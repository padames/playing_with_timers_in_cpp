#ifndef SSTHREAD_H
#define SSTHREAD_H

#include <thread>
#include <functional>
#include <iostream>
#include "Cancellation.h"

class Cancellation;

class SSThread
{
public:
    void start();
    void stop();
private:
    void run();
    std::unique_ptr<std::thread> thread_;
    Cancellation cpoint_;
};
#endif