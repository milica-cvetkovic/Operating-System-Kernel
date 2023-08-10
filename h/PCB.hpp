
#ifndef PROJECT_BASE_V1_1_PCB_HPP
#define PROJECT_BASE_V1_1_PCB_HPP

#include "../lib/hw.h"
#include "../lib/mem.h"
#include "../h/MemoryAllocator.hpp"
#include "scheduler.hpp"
#include "../h/syscall_c.hpp"

class PCB{

public:

    ~PCB() {
        //__mem_free(stack);
        MemoryAllocator::deallocate(stack);
    }

    bool is_finished() const { return finished;}

    void set_finished(bool f) { finished = f;}

    using Body = void (*)(void*);

    static int thread_create(PCB** handle, Body body, void* arg);

    static int create_thread(PCB** handle, Body body, void* arg);

    static void yield();

    static int thread_exit();

    static void start_thread(PCB* handle);

    static PCB* running;

    static void *operator new(size_t n);

    static void *operator new[](size_t n);

    static void operator delete(void *p);

    static void operator delete[](void *p);

    PCB(){}

private:

    //PCB(Body b, void* a): body(b), arg(a), stack(body != nullptr ? (uint64*)MemoryAllocator::allocate((sizeof(uint64)*DEFAULT_STACK_SIZE)): nullptr), context({(uint64)&thread_wrapper, stack != nullptr ? (uint64)&stack[DEFAULT_STACK_SIZE] : 0}), finished(false){

    //}

    PCB(Body b, void* a){
        body = b;
        arg = a;
        //stack = body != nullptr ? (uint64*)__mem_alloc(sizeof(uint64) * DEFAULT_STACK_SIZE): nullptr;
        stack = body != nullptr ? (uint64*)MemoryAllocator::allocate(sizeof(uint64) * DEFAULT_STACK_SIZE): nullptr;
        context = {(uint64)&thread_wrapper, stack != nullptr ? (uint64)&stack[DEFAULT_STACK_SIZE] : 0};
        finished=false;
        sem_closed = false;
    }

    struct Context {
        uint64 ra;
        uint64 sp;
    };

    Body body;
    void* arg;
    uint64* stack;
    Context context;
    bool finished;
    bool sem_closed;

    friend class General;
    friend class Sem;

    static void thread_wrapper();

    static void context_switch(Context* old_context, Context* running_context);

    static void dispatch();

};

#endif //PROJECT_BASE_V1_1_PCB_HPP
