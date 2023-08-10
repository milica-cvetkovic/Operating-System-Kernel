
#ifndef PROJECT_BASE_V1_1_SYSCALL_C_HPP
#define PROJECT_BASE_V1_1_SYSCALL_C_HPP

#include "../lib/hw.h"
#include "../h/PCB.hpp"

void* mem_alloc(size_t size);

int mem_free(void* addr);

class PCB;

typedef PCB* thread_t;

int thread_create(thread_t* handle,void(*start_routine)(void*), void* arg);

int create_thread(thread_t* handle,void(*start_routine)(void*), void* arg);

void thread_dispatch();

int thread_exit();

void start_thread(thread_t thread);

class Sem;

typedef Sem* sem_t;

int sem_open(sem_t* handle, unsigned init);

int sem_close(sem_t handle);

int sem_wait(sem_t id);

int sem_signal(sem_t id);

char getc();

void putc(char c);


#endif //PROJECT_BASE_V1_1_SYSCALL_C_HPP
