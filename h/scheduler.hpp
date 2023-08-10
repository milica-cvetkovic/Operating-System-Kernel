//
// Created by os on 6/22/22.
//

#ifndef PROJECT_BASE_V1_1_SCHEDULER_HPP
#define PROJECT_BASE_V1_1_SCHEDULER_HPP

#include "list.hpp"

class PCB;

class Scheduler{

private:

    static List<PCB> Queue;

public:

    static PCB* get();
    static void put(PCB* thread);


};

#endif //PROJECT_BASE_V1_1_SCHEDULER_HPP
