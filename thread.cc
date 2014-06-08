// thread.cc
// Header for thread class in C++.
// Copyright © 2014 Daniel

#include "thread.h"
using namespace multi;

static void* runThread(void* arg)
{
    return ((thread*)arg)->run();
}

thread::thread():tid(0), running(false), detached(false) {}

thread::~thread() {
    if (running == true && detached == false) {
        pthread_detach(tid);
    }
    if (running == true) {
        pthread_cancel(tid);
    }
}

int thread::start()
{
    int res = pthread_create(&tid, NULL, runThread, this);
    if (res == 0) {
        running = true;
    }
    return res;
}

int thread::join()
{
    int res = -1;
    if (running == true) {
        res = pthread_join(tid, NULL);
        if (res == 0) {
            detached = false;
        }
    }
    return res;
}

int thread::detach()
{
    int res = -1;
    if (running == 1 && detached == 0) {
        res = pthread_detach(tid);
        if (res == 0) {
            detached = 1;
        }
    }
    return res;
}

pthread_t thread::self() {
    return tid;
}
