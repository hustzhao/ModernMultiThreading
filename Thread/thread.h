#ifndef THREAD_H
#define THREAD_H
#include <iostream>
#include <pthread.h>
#include <memory>
#include <errno.h>
#include <string.h>

class Runnable {
public:
    virtual void* run() = 0;
    virtual ~Runnable() = 0;
};

class Thread
{
public:
    Thread(std::shared_ptr<Runnable> runnable, bool detached = false);
    Thread(bool detached = false);
    virtual ~Thread();
    void start();
    void *join();
private:
    Thread(const Thread&);
    const Thread& operator =(const Thread&);

    pthread_t thread_id_;
    std::shared_ptr<Runnable> runnable_;
    bool detached_;
    pthread_attr_t thread_attribute_;
    void* result_;

    void setCompleted();
    virtual void* run(){}
    static void* start_thread_runnable(void* arg);
    static void* start_thread(void* arg);
    void print_error(const char* msg, int status, const char* function_name,int line_number);
    void check_status(const char* msg, int status);
};

#endif // THREAD_H
