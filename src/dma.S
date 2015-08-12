
    #include "n64.inc"

    .global dmaCopy
    .type   dmaCopy, @function
// void dmaCopy(void *dest, void *src, size_t len);
dmaCopy:
    .set noat
    .set noreorder

    lui $t0,PI_BASE // A0 = PI Base Register ($A4600000)
0:
        lb $t1,PI_STATUS($t0) // T0 = Byte From PI Status Register ($A4600010)
        sync // Sync Load
        andi $t1,3 // AND PI Status With 3
        bnez $t1,0b // IF TRUE DMA Is Busy
        nop // Delay Slot

    li $t2,0x7FFFFF
    and $t1,$a0,$t2
    // la $t1,\dest&0x7FFFFF // T0 = Aligned DRAM Physical RAM Offset ($00000000..$007FFFFF 8MB)
    sw $t1,PI_DRAM_ADDR($t0) // Store RAM Offset To PI DRAM Address Register ($A4600000)
    li $t2,0x3FFFFFF
    li $t3,0x10000000
    and $t1,$a1,$t2
    or $t1,$t1,$t3
    // la $t1,0x10000000|(start&0x3FFFFFF) // T0 = Aligned Cart Physical ROM Offset ($10000000..$13FFFFFF 64MB)
    sw $t1,PI_CART_ADDR($t0) // Store ROM Offset To PI Cart Address Register ($A4600004)
    addi $t1,$a2,-1
    // la $t1,(\end-\start)-1 // T0 = Length Of DMA Transfer In Bytes - 1
    sw $t1,PI_WR_LEN($t0) // Store DMA Length To PI Write Length Register ($A460000C)
    jr $ra
    nop
    .size dmaCopy,.-dmaCopy

// vim:ft=mips
