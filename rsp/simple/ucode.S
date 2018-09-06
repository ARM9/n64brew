
#include "rsp_cop2.inc"

    .balign 16
    .global ucode
ucode:
    .set noat; .set noreorder

    lqv v0, 0, R_ZERO
    lqv v1, 1, R_ZERO

    vadd v0, v0, v1

    sqv v0, 0, R_ZERO
    nop
    nop

    break
    nop

    .global ucode_data
    .global ucode_data_len
    .balign 16
ucode_data:
    .hword 100,200,300,400,500,600,700,800
    .hword 1,1,1,1,1,1,1,1
ucode_data_len: .word (. - ucode_data - 1) | 7

// vim: ft=mips
