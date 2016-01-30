
    #include "input.h"
    #include "si.h"

    .text
    .balign 4
    .global initJoypad
    .type initJoypad, @function
initJoypad:
    .set noat; .set noreorder

    li $t0, SI_BASE // A0 = SI Base Register ($A4800000)
    la $t1, _PIF1 // A1 = _PIF1 Offset
    sw $t1,  SI_DRAM_ADDR($t0) // Store _PIF1 To SI_DRAM_ADDR ($A4800000)
    la $t2, PIF_RAM // A1 = PIF_RAM: JoyChannel ($BFC007C0)
    jr $ra
    sw $t2, SI_PIF_ADDR_WR64B($t0) // 64 Byte Write DRAM -> PIF ($A4800010)

    .size initJoypad, .-initJoypad

    .text
    .balign 4
    .global updateJoypads
    .type updateJoypads, @function
updateJoypads:
    .set noat; .set noreorder

 // maybe move this to readJoypad?
    li $t0, PIF_BASE // A0 = PIF Base Register ($BFC00000)
    li $t1, SI_BASE // A1 = SI Base Register ($A4800000)
    la $t2, _controller_state // A2 = _controller_state Offset
    sw $t2,  SI_DRAM_ADDR($t1) // Store _controller_state To SI_DRAM_ADDR ($A4800000)
    ori $t2,$t0, (PIF_RAM) // A2 = PIF_RAM: JoyChannel ($BFC007C0)
    sw $t2,  SI_PIF_ADDR_RD64B($t1) // 64 Byte Read PIF -> DRAM ($A4800004)

     // lhu $t3, PIF_HWORD($t0) // T0 = Buttons ($BFC007C4)
     // lhu $t4, PIF_XBYTE($t0)
     // sh $t3, 0($a0)
     // sh $t4, 2($a0)

    jr $ra
    nop

    .size updateJoypads, .-updateJoypads

    .text
    .balign 4
    .globl readJoypad
    .type readJoypad, @function
readJoypad:
    .set noat; .set noreorder

.equ pad_num, $a0
.equ joy_t, $a1

    // t0 = _controller_state + 4 + pad_num * 8
    // la $t0, _controller_state+4
    li $t0, PIF_HWORD// _controller_state+4
    sll pad_num, 3
    addu $t0, pad_num

    lhu $t1, 0($t0) // t1 = buttons
    lhu $t2, 2($t0) // t2 = low analog X, high analog Y
    nop
    sh $t1, 0(joy_t)  // store buttons in Joypad_t
    sh $t2, 2(joy_t)  // store analog stick
    jr $ra
    nop
    
    .size readJoypad, .-readJoypad

    .data
    .balign 64
_PIF1:
    .word 0xFF010401 // enable controller 1?
    .word 0xFFFFFFFF
    .word 0xFF010401 // enable controller 2?
    .word 0xFFFFFFFF
    .word 0xFF010401
    .word 0xFFFFFFFF
    .word 0xFF010401 // enable controller 4?
    .word 0xFFFFFFFF
    .word 0xFE000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000001
 
    .balign 64
_controller_state:
    .fill 64, 0

// vim:ft=mips
