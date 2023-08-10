#include "../h/Sem.hpp"

int Sem::open(Sem** handle, unsigned init){
    *handle = new Sem(init);
    if(handle == nullptr) return -1;
    return 0;
}

int Sem::close(Sem* handle){
    while(true){
        PCB* thr = handle->blocked->remove_first();
        if(thr == nullptr) break;
        thr->sem_closed=true;
    };
    return 0;
}

int Sem::wait(Sem* handle){

    if(PCB::running->sem_closed) return -1;

    if(--handle->val<0){
        PCB* old = PCB::running;
        handle->put_blocked(old);
        PCB::running = Scheduler::get();
        PCB::context_switch(&old->context, &PCB::running->context);
    }
    return 0;
}

int Sem::signal(Sem* handle){

    if(++handle->val<=0){
        PCB* thr = handle->get_blocked();
        if(thr) Scheduler::put(thr);
    }

    return 0;
}

void *Sem::operator new(size_t n){
    //return __mem_alloc(n);
    return MemoryAllocator::allocate(n);
}

void Sem::operator delete(void *p){
    //__mem_free(p);
    MemoryAllocator::deallocate(p);
}

void Sem::put_blocked(PCB* thr){
    blocked->add_last(thr);
}

PCB* Sem::get_blocked(){
    return blocked->remove_first();
}

