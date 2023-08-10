//
// Created by os on 6/23/22.
//

#ifndef PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
#define PROJECT_BASE_V1_1_SYSCALL_CPP_HPP

#include "../lib/hw.h"
#include "syscall_c.hpp"

void* operator new (size_t size);

void operator delete (void* addr);


class Thread {

public:

    Thread (void (*body)(void*), void* arg);

    virtual ~Thread ();

    int start ();

    static void dispatch ();

    static int sleep (time_t);

    static void wrapper(void *thread);

protected:

    Thread ();

    virtual void run () {}

private:

    thread_t myHandle;

};


class Semaphore {

public:

    Semaphore (unsigned init = 1);

    virtual ~Semaphore ();

    int wait ();

    int signal ();

private:

    sem_t myHandle;

};


#endif //PROJECT_BASE_V1_1_SYSCALL_CPP_HPP
