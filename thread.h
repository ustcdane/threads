// thread.h
// Header for thread class in C++.
// Copyright © 2014 Daniel

#ifndef __thread_h__
#define __thread_h__

#include <pthread.h>

namespace multi
{
class thread
{
public:
    thread();
    virtual ~thread();

    int start();
    int join();
    int detach();
    pthread_t self();

    virtual void* run() = 0;

private:
    pthread_t tid;
    bool running;
    bool detached;
};

}
#endif
