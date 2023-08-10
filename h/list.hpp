//
// Created by os on 6/22/22.
//

#ifndef PROJECT_BASE_V1_1_LIST_HPP
#define PROJECT_BASE_V1_1_LIST_HPP

#include "../lib/mem.h"
#include "../h/MemoryAllocator.hpp"
#include "../lib/console.h"

template<typename T>
class List{

private:

    struct Elem{
        T* data;
        Elem* next;

        void *operator new(size_t size) {
            return MemoryAllocator::allocate(size);
            //return __mem_alloc(size);
        }

        void operator delete(void* addr){
            //__mem_free(addr);
            MemoryAllocator::deallocate(addr);
        }

        Elem(T* data, Elem* next): data(data), next(next){}

    };

    Elem* head, *tail;

public:

    void *operator new(size_t size) {
        return MemoryAllocator::allocate(size);
        //return __mem_alloc(size);
    }

    void operator delete(void* addr){
        //__mem_free(addr);
        MemoryAllocator::deallocate(addr);
    }

    void set_head_tail() {
        head = nullptr;
        tail = nullptr;
    }

    List(): head(0), tail(0) {}

    List(const List<T>&) = delete;
    List<T> &operator=(const List<T>&) = delete;

    void add_first(T* data){
        Elem* elem = new Elem(data, head);
        head = elem;
        if (tail != nullptr) { tail = head;}
    }

    void add_last(T* data){
        Elem* elem = new Elem(data, 0);
        if(tail){
            tail->next = elem;
            tail = elem;
        }
        else{
            head = tail = elem;
        }
    }

    T* remove_first(){

        if(!head){ return 0;}

        Elem* elem = head;
        head = head->next;

        if(!head) { tail = 0;}
        T* ret = elem->data;
        //__mem_free(elem);
        MemoryAllocator::deallocate(elem);
        return ret;
    }

    T* see_first(){
        if(!head) {return 0;}
        return head->data;
    }

    T* remove_last(){
        if(!head) { return 0;}

        Elem* prev = 0;
        for(Elem* temp = head; temp && temp!= tail;temp=temp->next){
            prev = temp;
        }

        Elem* elem = tail;
        if(prev) {prev->next = 0;}
        else {head = 0;}
        tail = prev;

        T* ret = elem->data;
        MemoryAllocator::deallocate(elem);
        //delete elem;
        return ret;
    }

    T* see_last(){
        if(!tail) { return 0;}
        return tail->data;
    }

};


#endif //PROJECT_BASE_V1_1_LIST_HPP
