#include "../h/general.hpp"

void General::pop_spp_spie() {
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}

using Body = void (*)(void*);

void General::handle_trap() {

    uint64 scause;
    __asm__ volatile("csrr %[scause], scause" : [scause] "=r"(scause));

    if (scause == 0x0000000000000009UL){

        uint64 sepc, sstatus;
        __asm__ volatile ("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
        __asm__ volatile ("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));
        sepc+=4;
        sstatus&= ~(1 << 8);
        __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
        __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));

    }
    else if(scause == 0x0000000000000008UL ){

        uint64 reg = 0;
        __asm__ volatile("ld %0, 80(s0)":"=r"(reg));

        if(reg == 0x01){
            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            size_t size = 0;
            __asm__ volatile("ld %0, 88(s0)":"=r"(size));

            //__mem_alloc(size);
            MemoryAllocator::allocate(size);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));

        }
        else if(reg== 0x02){

            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            void* addr = nullptr;
            __asm__ volatile("ld %0, 88(s0)":"=r"(addr));

            //__mem_free(addr);
            MemoryAllocator::deallocate(addr);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
        }
        else if(reg == 0x11){

            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            PCB** handle = 0;
            __asm__ volatile("ld %0, 88(s0)":"=r"(handle));
            Body body = 0;
            __asm__ volatile("ld %0, 96(s0)":"=r"(body));
            void* arg = 0;
            __asm__ volatile("ld %0, 104(s0)":"=r"(arg));

            PCB::thread_create(handle, body, arg);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));


        }
        else if (reg==0x12){
            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            PCB::thread_exit();

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
        }
        else if(reg == 0x13) {

            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            PCB::dispatch();

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));

        }
        else if(reg == 0x14){
            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            PCB** handle = 0;
            __asm__ volatile("ld %0, 88(s0)":"=r"(handle));
            Body body = 0;
            __asm__ volatile("ld %0, 96(s0)":"=r"(body));
            void* arg = 0;
            __asm__ volatile("ld %0, 104(s0)":"=r"(arg));

            PCB::create_thread(handle, body, arg);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
        }
        else if (reg == 0x15){
            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            PCB* handle = 0;
            __asm__ volatile("ld %0, 88(s0)":"=r"(handle));

            PCB::start_thread(handle);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));

        }
        else if(reg == 0x21){

            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            Sem** handle = 0;
            __asm__ volatile("ld %0, 88(s0)":"=r"(handle));
            int init = 0;
            __asm__ volatile("ld %0, 96(s0)":"=r"(init));

            Sem::open(handle, init);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));

        }
        else if(reg == 0x22){
            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            Sem* handle = 0;
            __asm__ volatile("ld %0, 88(s0)":"=r"(handle));

            Sem::close(handle);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
        }
        else if(reg == 0x23){
            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            Sem* handle = 0;
            __asm__ volatile("ld %0, 88(s0)":"=r"(handle));

            Sem::wait(handle);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
        }
        else if(reg == 0x24){
            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            Sem* handle = 0;
            __asm__ volatile("ld %0, 88(s0)":"=r"(handle));

            Sem::signal(handle);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));
        }
        else if(reg == 0x41){

            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            __getc();

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));

        }
        else if(reg == 0x42){

            uint64 sepc;
            __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
            sepc+=4;

            uint64 sstatus;
            __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

            char c = 0;
            __asm__ volatile("ld %0, 88(s0)":"=r"(c));

            __putc(c);

            asm("sd a0, 80(s0)");

            __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
            __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));

        }

    }
    else if(scause == 0x8000000000000001UL){

        uint64 sepc;
        __asm__ volatile("csrr %[sepc], sepc" : [sepc] "=r"(sepc));
        uint64 sstatus;
        __asm__ volatile("csrr %[sstatus], sstatus" : [sstatus] "=r"(sstatus));

        uint64 mask = (1 << 1);
        __asm__ volatile ("csrc sip, %[mask]" : : [mask] "r"(mask));


        __asm__ volatile ("csrw sstatus, %[sstatus]" : : [sstatus] "r"(sstatus));
        __asm__ volatile ("csrw sepc, %[sepc]" : : [sepc] "r"(sepc));

    }
    else if(scause == 0x8000000000000009UL){
        console_handler();
    }
    else{
        printInt(scause);
    }

}