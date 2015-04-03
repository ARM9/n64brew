    .include "n64.inc"

    .text
    .align 2
    .global initJoypad
    .type initJoypad, @function
initJoypad:
    .set noat; .set noreorder

    lui $t0, SI_BASE # A0 = SI Base Register ($A4800000)
    la $t1, PIF1 # A1 = PIF1 Offset
    sw $t1, SI_DRAM_ADDR($t0) # Store PIF1 To SI_DRAM_ADDR ($A4800000)
    la $t2, ((PIF_BASE<<16)|PIF_RAM) # A1 = PIF_RAM: JoyChannel ($BFC007C0)
    jr $ra
    sw $t2, SI_PIF_ADDR_WR64B($t0) # 64 Byte Write DRAM -> PIF ($A4800010)

    .size initJoypad, .-initJoypad

    .text
    .align 2
    .global readJoypad
    .type readJoypad, @function
readJoypad:
    .set noat; .set noreorder

    lui $t0, PIF_BASE # A0 = PIF Base Register ($BFC00000)
    lui $t1, SI_BASE # A1 = SI Base Register ($A4800000)
    la $t2, PIF2 # A2 = PIF2 Offset
    sw $t2, SI_DRAM_ADDR($t1) # Store PIF2 To SI_DRAM_ADDR ($A4800000)
    ori $t2,$t0, PIF_RAM # A2 = PIF_RAM: JoyChannel ($BFC007C0)
    sw $t2, SI_PIF_ADDR_RD64B($t1) # 64 Byte Read PIF -> DRAM ($A4800004)

    lhu $t3, PIF_HWORD($t0) # T0 = Buttons ($BFC007C4)
    lhu $t4, PIF_XBYTE($t0)
    nop
    sh $t3, 0($a0)  # store buttons in Joy_t
    jr $ra
    sh $t4, 2($a0)  # store analog stick

    .size readJoypad, .-readJoypad

    .align 6
    .data
PIF1:
    .word 0xFF010401 # enable controller 1?
    .word 0x00000000
    .word 0xFF010401 # enable controller 2?
    .word 0x00000000
    .word 0xFF010401
    .word 0x00000000
    .word 0xFF010401 # enable controller 4?
    .word 0x00000000
    .word 0xFE000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000001
 
PIF2:
    .fill 64, 0

# vim:ft=mips
