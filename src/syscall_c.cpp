#include "../h/syscall_c.hpp"

void* mem_alloc(size_t size){

//    size_t blocks = size/MEM_BLOCK_SIZE;
//    if(size%MEM_BLOCK_SIZE) blocks++;
//    size = blocks;

    uint64 code = 0x01;
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(size));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    void* ret = nullptr;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;

}

int mem_free(void* addr){

    uint64 code = 0x02;
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(addr));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    int ret = 0;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;
}


int thread_create(thread_t* handle,void(*start_routine)(void*), void* arg){

    uint64 code = 0x11;
    __asm__ volatile ("mv a3, %[val]"::[val]"r"(arg));
    __asm__ volatile ("mv a2, %[val]"::[val]"r"(start_routine));
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(handle));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    int ret = 0;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;

}

void thread_dispatch(){

    uint64 code = 0x13;

    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    return;

}

int thread_exit(){

    uint64 code = 0x12;

    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    int ret = 0;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;

}

int create_thread(thread_t* handle,void(*start_routine)(void*), void* arg){

    uint64 code = 0x14;
    __asm__ volatile ("mv a3, %[val]"::[val]"r"(arg));
    __asm__ volatile ("mv a2, %[val]"::[val]"r"(start_routine));
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(handle));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    int ret = 0;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;

}

void start_thread(thread_t thread){

    uint64 code = 0x15;
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(thread));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    return;

}

int sem_open(sem_t* handle, unsigned init){

    uint64 code = 0x21;
    __asm__ volatile ("mv a2, %[val]"::[val]"r"(init));
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(handle));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    int ret = 0;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;

}

int sem_close(sem_t handle){

    uint64 code = 0x22;
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(handle));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    int ret = 0;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;

}

int sem_wait(sem_t id){

    uint64 code = 0x23;
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(id));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    int ret = 0;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;

}

int sem_signal(sem_t id){

    uint64 code = 0x24;
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(id));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    int ret = 0;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;

}

const int EOF = -1;

char getc(){

    uint64 code = 0x41;
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    char ret = 0;

    __asm__ volatile("mv %[val], a0":[val]"=r"(ret));

    return ret;

}

void putc(char c){

    uint64 code = 0x42;
    __asm__ volatile ("mv a1, %[val]"::[val]"r"(c));
    __asm__ volatile ("mv a0, %[val]"::[val]"r"(code));

    __asm__ volatile ("ecall");

    return;

}