#include "../h/syscall_cpp.hpp"

void Thread::wrapper(void *thread) {
    ((Thread*)thread)->run();
}

void* operator new (size_t size){
    return mem_alloc(size);
}

void operator delete (void* addr){
    mem_free(addr);
}

using Body = void (*)(void*);

Thread::Thread(Body body, void* arg){
    create_thread(&myHandle, body, arg);
}

Thread::Thread (){
    create_thread(&myHandle, wrapper , this);
}

int Thread::start() {
    //thread_create(&myHandle, wrapper , this);
    start_thread(myHandle);
    return 0;
}

void Thread::dispatch (){
    thread_dispatch();
}

Thread::~Thread (){
    delete myHandle;
}


Semaphore::Semaphore (unsigned init){
    sem_open(&myHandle,init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait (){
    return sem_wait(myHandle);
}

int Semaphore::signal (){
    return sem_signal(myHandle);
}