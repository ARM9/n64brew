
    #include "rcp/vi.h"

    .balign 4
    .global swapFramebuffer
    .type swapFramebuffer,@function
swapFramebuffer:
    .equ Framebuffer_t_ptr,$a0

    .equ vi_ptr,    $t0
    .equ fb_ptr,    $t1
    .equ fb_size,   $t2
    .equ tmp,       $t3

    .set noat; .set noreorder
    lw fb_ptr,0(Framebuffer_t_ptr)
    li vi_ptr,VI_BASE // VI Base Register (0xA4400000)
    lw fb_size,12(Framebuffer_t_ptr) // screen size in bytes

    sw fb_ptr, VI_ORIGIN(vi_ptr) // Store Origin To VI Origin Register (0xA4400004)
    xor tmp,fb_ptr,fb_size  // Flip framebuffer page

    sw tmp,0(Framebuffer_t_ptr) // Store back new framebuffer pointer
    jr $ra
    nop

    .size swapFramebuffer,.-swapFramebuffer


    .balign 4
    .global waitScanline
    .type waitScanline,@function
waitScanline:
    .equ vi_ptr,$t0
    .equ tmp,   $t1

    .set noat; .set noreorder
    li vi_ptr,VI_BASE // VI Base Register (0xA4400000)
0:
    lw tmp,VI_V_CURRENT_LINE(vi_ptr) // tmp = Current Scan Line
    //sync // Sync Load
    bne tmp,$a0,0b // IF (Current Scan Line != Scan Line) Wait
    nop
    jr $ra
    nop // Delay Slot

    .size waitScanline,.-waitScanline

// vim:ft=mips
