.global _ZN7General14push_registersEv
.type _ZN7General14push_registersEv, @function
_ZN7General14push_registersEv:
    addi sp, sp, -256
    .irp index, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index*8(sp)
    .endr
    ret

.global _ZN7General13pop_registersEv
.type _ZN7General13pop_registersEv, @function
_ZN7General13pop_registersEv:
    .irp index, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index*8(sp)
    .endr
    addi sp, sp, 256
    ret