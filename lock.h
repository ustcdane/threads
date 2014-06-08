// lock.h
// Header for thread lock( mutex condition_variable) in C++.
// mutex, lock_guard, condition_var
// Copyright © 2014 Daniel

#ifndef _LOCK_H_
#define _LOCK_H_

#include<pthread.h>

namespace multi {

class mutex
{
public:
    mutex() {
        pthread_mutex_init(&mutex_, NULL);
    }

    ~mutex() {
        pthread_mutex_destroy(&mutex_);
    }

    bool lock() {
        if (pthread_mutex_lock(&mutex_)) {
            return false;
        }
        return true;
    }

    bool time_lock(int us_) {
        timespec ts = {us_/(1000000), us_*(1000)};
        if (pthread_mutex_timedlock(&mutex_, &ts)){
            return false;
        }
        return true;
    }

    bool unlock() {
        if (pthread_mutex_unlock(&mutex_)) {
        return false;
        }
        return true;
    }

    bool try_lock() {
        if (pthread_mutex_trylock(&mutex_)) {
                return false;
        }
        return true;
    }

    pthread_mutex_t& get_mutex() {
        return mutex_;
    }

private:
    pthread_mutex_t              mutex_;
};

class lock_guard
{
public:
    lock_guard(mutex& mx):flag(false),mutex_(mx) {
        mutex_.lock();
        flag = true;
    }

    ~lock_guard() {
        if (is_locked()) {
            unlock();
        }
    }

    bool unlock() {
        flag = false;
        return mutex_.unlock();
    }

    bool is_locked() const {
        return flag;
    }

private:
    bool    flag;
    mutex&  mutex_;
};


class condition_var
{
public:
    condition_var(mutex& mx):mutex_(mx) {
        pthread_cond_init(&cond, NULL);
    }

    ~condition_var() {
        pthread_cond_destroy(&cond);
    }

    bool wait() {
        return 0 == pthread_cond_wait(&cond, &mutex_.get_mutex());
    }

    bool time_wait(int us_) {
        timespec ts = {us_/(1000000), us_*(1000)};
        return 0 == pthread_cond_timedwait(&cond, &mutex_.get_mutex(), &ts);
    }

    bool signal() {
        return 0 == pthread_cond_signal(&cond);
    }

    bool broadcast() {
         return 0 == pthread_cond_broadcast(&cond);
    }

private:
    mutex&    mutex_;
    pthread_cond_t  cond;
};

}
#endif

