#include "../h/MemoryAllocator.hpp"
#include "../lib/hw.h"
#include "../lib/console.h"
#include "../h/syscall_c.hpp"
#include "../h/general.hpp"

#include "../h/syscall_cpp.hpp"

//#include "../test/Threads_C_API_test.hpp" // zadatak 2, niti C API i sinhrona promena konteksta
//#include "../test/Threads_CPP_API_test.hpp" // zadatak 2., niti CPP API i sinhrona promena konteksta

//#include "../test/ConsumerProducer_C_API_test.h" // zadatak 3., kompletan C API sa semaforima, sinhrona promena konteksta
#include "../test/ConsumerProducer_CPP_Sync_API_test.hpp" // zadatak 3., kompletan CPP API sa semaforima, sinhrona promena konteksta

//#include "../test/ThreadSleep_C_API_test.hpp" // thread_sleep test C API
//#include "../test/ConsumerProducer_CPP_API_test.hpp" // zadatak 4. CPP API i asinhrona promena konteksta

void userMain() {
    //Threads_C_API_test(); // zadatak 2., niti C API i sinhrona promena konteksta
    //Threads_CPP_API_test(); // zadatak 2., niti CPP API i sinhrona promena konteksta

    //producerConsumer_C_API(); // zadatak 3., kompletan C API sa semaforima, sinhrona promena konteksta
    producerConsumer_CPP_Sync_API(); // zadatak 3., kompletan CPP API sa semaforima, sinhrona promena konteksta

    //testSleeping(); // thread_sleep test C API
    //ConsumerProducerCPP::testConsumerProducer(); // zadatak 4. CPP API i asinhrona promena konteksta, kompletan test svega

}

void wrapper(void* arg){
    userMain();
}


int main(){

    MemoryAllocator::initialize();
    uint64 stvec = (uint64)&General::trap;
    __asm__ volatile ("csrw stvec, %[stvec]" : : [stvec] "r"(stvec));

    uint64 mask = (1 << 5);
    __asm__ volatile ("csrc sstatus, %[mask]" : : [mask] "r"(mask));

    PCB* sysMain = 0;
    PCB::thread_create(&sysMain, nullptr, nullptr);
    PCB::running = sysMain;

    __asm__ volatile("ecall");

    PCB* userMain;
    thread_create(&userMain, wrapper, nullptr);
    while(!userMain->is_finished()) thread_dispatch();


    return 0;
}

void userMain();