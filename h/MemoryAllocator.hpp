//
// Created by os on 6/20/22.
//

#ifndef PROJECT_MEMORYALLOCATOR_HPP
#define PROJECT_MEMORYALLOCATOR_HPP

#include "../lib/hw.h"

typedef struct free_mem{
    size_t size;
    struct free_mem* next;
    struct free_mem* prev;
} free_mem;


class MemoryAllocator{

public:

    static free_mem* free_mem_head;
    static size_t max_memory;

    static void initialize();

    static void* allocate(size_t size);
    static int deallocate(void* addr);
};

#endif //PROJECT_MEMORYALLOCATOR_HPP
