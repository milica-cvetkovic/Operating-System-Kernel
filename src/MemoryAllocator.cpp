//
// Created by os on 6/16/22.

#include "../lib/hw.h"
#include "../h/MemoryAllocator.hpp"

free_mem* MemoryAllocator::free_mem_head = (free_mem*)HEAP_START_ADDR;
size_t MemoryAllocator::max_memory = ((size_t)HEAP_END_ADDR - (size_t)HEAP_START_ADDR - sizeof(free_mem));

void MemoryAllocator::initialize() {
    free_mem_head = (free_mem*)HEAP_START_ADDR;
    free_mem_head->size =((size_t)HEAP_END_ADDR - (size_t)HEAP_START_ADDR - sizeof(free_mem));
    free_mem_head->next= nullptr;
    free_mem_head->prev= nullptr;
    max_memory = ((size_t)HEAP_END_ADDR - (size_t)HEAP_START_ADDR - sizeof(free_mem));
}

void* MemoryAllocator::allocate(size_t size){
    size_t blocks = size/MEM_BLOCK_SIZE;
    if(size%MEM_BLOCK_SIZE) blocks++;
    size = blocks*MEM_BLOCK_SIZE;
    //size = size*MEM_BLOCK_SIZE;
    if(size > max_memory) return nullptr;
    free_mem* temp = free_mem_head;
    for(;temp; temp=temp->next)
        if(temp->size >= size) break;

    //nema dovoljno prostora
    if(temp == nullptr){
        return nullptr;
    }

    void* ret = (char*)temp + sizeof(free_mem);
    if(temp->size - size >= sizeof(free_mem) + MEM_BLOCK_SIZE) {
        size_t new_size = temp->size - size - sizeof(free_mem);
        free_mem *old_next = temp->next;
        free_mem* old_prev = temp->prev;
        temp->size = size;
        temp = (free_mem *) ((char *) temp + size + sizeof(free_mem));
        if (old_prev == nullptr) free_mem_head = temp;
        temp->size = new_size;
        temp->next = old_next;
        temp->prev = old_prev;
        if(temp->prev) temp->prev->next = temp;
        else free_mem_head = temp;
        if(temp->next) temp->next->prev = temp;
    }
    else{
        if(temp->prev) temp->prev->next = temp->next;
        else free_mem_head=temp->next;
        if(temp->next) temp->next->prev = temp->prev;
    }

    return ret;

}

int MemoryAllocator::deallocate(void* addr){
    if(addr == nullptr) return -1;
    addr = (char*)addr - sizeof(free_mem);

    free_mem* new_elem = (free_mem*) addr;
    free_mem* temp = nullptr;
    if(free_mem_head == nullptr || addr < (char*)free_mem_head);
    else
        for(temp=free_mem_head; temp->next != nullptr && (char*)new_elem>(char*)(temp->next); temp=temp->next);

    //ako mogu da se nadovezu dva slobodna segmenta

    if (temp && (char*)temp + temp->size + sizeof(free_mem) == (char*)new_elem) {
        //prethodni segment
        temp->size += new_elem->size + sizeof(free_mem);
        if (temp->next && (char *) temp + temp->size + sizeof(free_mem )== (char *) (temp->next)) {
            //naredni segment
            temp->size += temp->next->size + sizeof(free_mem);
            temp->next = temp->next->next;
            if(temp->next) temp->next->prev = temp;
        }
        return 0;
    }
    if (temp && (char*) new_elem + sizeof(free_mem) + new_elem->size == (char*)temp) {
        //naredni segment
        new_elem->size = new_elem->size + temp->size + sizeof(free_mem);
        new_elem->next = temp->next;
        new_elem->prev = temp->prev;
        if(temp->next) temp->next->prev = new_elem;
        if(temp->prev) temp->prev->next = new_elem;
        else free_mem_head = new_elem;
        return 0;
    }

    free_mem* next_elem = temp?temp->next:free_mem_head;
    if(next_elem && (char*)new_elem + new_elem->size + sizeof(free_mem) == (char*)next_elem){
        new_elem->size = new_elem->size + next_elem->size + sizeof(free_mem);
        new_elem->next = next_elem->next;
        new_elem->prev = next_elem->prev;
        if(next_elem->next) next_elem->next->prev = new_elem;
        if(next_elem->prev) next_elem->prev->next = new_elem;
        else free_mem_head = new_elem;
        return 0;
    }
    else{
        new_elem->prev = temp;
        if(temp) new_elem->next = temp->next;
        else new_elem->next=free_mem_head;
        if(new_elem->next) new_elem->next->prev = new_elem;
        if(temp) temp->next = new_elem;
        else free_mem_head = new_elem;

        return 0;
    }

}
