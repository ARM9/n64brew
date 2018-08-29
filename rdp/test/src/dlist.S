
    #include "rcp/rdp.h"

    .data
    .balign 8
asm_dp_list:
.quad \
set_scissor(0, 0, 0, 320<<2, 240<<2),\
set_other_modes(CYCLE_TYPE_FILL),\
set_color_image(IMAGE_DATA_FORMAT_RGBA, SIZE_OF_PIXEL_16B, 320-1, 0x00100000),\
set_fill_color(0x00010001),\
fill_rectangle(0, 0, 319<<2, 239<<2),\
sync_pipe,\
set_fill_color(0xF001F001),\
fill_triangle(1,0,0, 400,200,200, 97,0,-1,0, 96,0,-1,0, 0,0,0,0),\
sync_full
.equ asm_dp_list_size,.-asm_dp_list

    .text
    .balign 4
    .global drawMeAsm
drawMeAsm:
    .set at; .set reorder
    addiu $sp, -8
    sw $ra, 0($sp)
    li $a0, asm_dp_list
    li $a1, asm_dp_list_size
    jal rdp_exec
    nop

    lw $ra, 0($sp)
    addiu $sp, 8
    jr $ra
    nop

// vim:ft=mips
