#include "../h/PCB.hpp"
#include "../h/general.hpp"
#include "../h/scheduler.hpp"

PCB* PCB::running = nullptr;

int PCB::thread_create(PCB** handle, Body body, void*arg) {

    *handle = new PCB(body, arg);
    if(handle == nullptr) return -1;
    if(body != nullptr) { Scheduler::put(*handle);}
    return 0;
}

int PCB::create_thread(PCB** handle, Body body, void* arg){
    *handle = new PCB(body, arg);
    if(handle == nullptr) return -1;
    return 0;
}

int PCB::thread_exit() {
    running->set_finished(true);
    PCB::dispatch();
    return 0;
}

void PCB::start_thread(PCB* handle){
    Scheduler::put(handle);
}

void PCB::yield(){
//
//     General::push_registers();
//     PCB::dispatch();
//     General::pop_registers();

    uint64 code = 0x13;

    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile("ecall");


}

void PCB::dispatch(){

    PCB* old = running;
    if(!old->is_finished()){ Scheduler::put(old);}
    running=Scheduler::get();

    if(PCB::running) PCB::context_switch(&old->context, &running->context);

}

void PCB::thread_wrapper() {
    General::pop_spp_spie();
    running->body(running->arg);
    running->set_finished(true);
    //PCB::yield();
    thread_dispatch();
}

void * PCB::operator new(size_t n){
    //return __mem_alloc(n);
    return MemoryAllocator::allocate(n);
}

void * PCB::operator new[](size_t n){
    //return __mem_alloc(n);
    return MemoryAllocator::allocate(n);
}

void PCB::operator delete(void *p) {
    //__mem_free(p);
    MemoryAllocator::deallocate(p);
}

void PCB::operator delete[](void *p) {
    //__mem_free(p);
    MemoryAllocator::deallocate(p);
}
