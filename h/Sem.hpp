//
// Created by os on 6/25/22.
//

#ifndef PROJECT_BASE_V1_1_SEM_HPP
#define PROJECT_BASE_V1_1_SEM_HPP

#include "../h/list.hpp"
#include "../h/PCB.hpp"

class Sem{

public:

    Sem(int init) {
        val = init;
        blocked = new List<PCB>();
    }

    static int wait(Sem* handle);

    static int signal(Sem* handle);

    static int open(Sem** handle, unsigned init);

    static int close(Sem* handle);

    static void *operator new(size_t n);

    static void operator delete(void *p);

    void put_blocked(PCB* thr);

    PCB* get_blocked();


private:

    int val;
    List<PCB>* blocked;

};

#endif //PROJECT_BASE_V1_1_SEM_HPP
