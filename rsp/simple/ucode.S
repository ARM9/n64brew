
#include "rsp_cop2.inc"

    .balign 16
    .global ucode_start
    .global ucode_end
ucode_start:
    .set noat; .set noreorder

    lqv v0, 0, R_ZERO

    vnxor v0, v0, v1
    vnxor v0, v0, v1, 0

#define v2e3 v2, 3
    vnxor v0, v0, v2, 3
    vnxor v0, v0, v2e3

    break
    nop
    j ucode_start
    nop

ucode_end:

// vim: ft=mips
