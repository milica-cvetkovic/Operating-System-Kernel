#include "../h/scheduler.hpp"

List<PCB> Scheduler::Queue;

PCB* Scheduler::get(){
    return Queue.remove_first();
}

void Scheduler::put(PCB* thread){
    Queue.add_last(thread);
}