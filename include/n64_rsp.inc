#==============================
# N64 Reality Signal Processor
#==============================
# RSP CP2 128-Bit Vector Registers:
.equ v0, 0
.equ v1, 1
.equ v2, 2
.equ v3, 3
.equ v4, 4
.equ v5, 5
.equ v6, 6
.equ v7, 7
.equ v8, 8
.equ v9, 9
.equ v10, 10
.equ v11, 11
.equ v12, 12
.equ v13, 13
.equ v14, 14
.equ v15, 15
.equ v16, 16
.equ v17, 17
.equ v18, 18
.equ v19, 19
.equ v20, 20
.equ v21, 21
.equ v22, 22
.equ v23, 23
.equ v24, 24
.equ v25, 25
.equ v26, 26
.equ v27, 27
.equ v28, 28
.equ v29, 29
.equ v30, 30
.equ v31, 31

# RSP CP2 Vector Elements (128-Bit Vector = 16 Elements):
.equ e0,  0
.equ e1,  1
.equ e2,  2
.equ e3,  3
.equ e4,  4
.equ e5,  5
.equ e6,  6
.equ e7,  7
.equ e8,  8
.equ e9,  9
.equ e10, 10
.equ e11, 11
.equ e12, 12
.equ e13, 13
.equ e14, 14
.equ e15, 15

# RSP CP0 Control Registers (MTF0/MTC0):
.equ c0,  0 # RSP CP0 Control Register 00: I/DMEM Address For DMA (RW) (0x04040000)
.equ c1,  1 # RSP CP0 Control Register 01:   DRAM Address For DMA (RW) (0x04040004)
.equ c2,  2 # RSP CP0 Control Register 02: DMA READ  Length (DRAM -> I/DMEM) (RW) (0x04040008)
.equ c3,  3 # RSP CP0 Control Register 03: DMA WRITE Length (DRAM <- I/DMEM) (RW) (0x0404000C)
.equ c4,  4 # RSP CP0 Control Register 04: RSP Status (RW) (0x04040010)
.equ c5,  5 # RSP CP0 Control Register 05: DMA Full (R) (0x04040014)
.equ c6,  6 # RSP CP0 Control Register 06: DMA Busy (R) (0x04040018)
.equ c7,  7 # RSP CP0 Control Register 07: CPU-RSP Semaphore (RW) (0x0404001C)
.equ c8,  8 # RSP CP0 Control Register 08: RDP Command Buffer START (RW) (0x04100000)
.equ c9,  9 # RSP CP0 Control Register 09: RDP Command Buffer END (RW) (0x04100004)
.equ c10, 10 # RSP CP0 Control Register 10: RDP Command Buffer CURRENT (R) (0x04100008)
.equ c11, 11 # RSP CP0 Control Register 11: RDP Status (RW) (0x0410000C)
.equ c12, 12 # RSP CP0 Control Register 12: RDP Clock Counter (R) (0x04100010)
.equ c13, 13 # RSP CP0 Control Register 13: RDP Command Buffer BUSY (R) (0x04100014)
.equ c14, 14 # RSP CP0 Control Register 14: RDP Pipe BUSY (R) (0x04100018)
.equ c15, 15 # RSP CP0 Control Register 15: RDP TMEM BUSY (R) (0x0410001C)

# RSP CP2 Control Registers (CFC2/CTC2):
.equ VCO, 0 # RSP CP2 Control Register 0: Vector Carry Out
.equ VCC, 1 # RSP CP2 Control Register 1: Vector Compare Code
.equ VCE, 2 # RSP CP2 Control Register 2: Vector Compare Extension

# SP Status Read Flags:
.equ RSP_HLT, 0x0001 # SP_STATUS: Halt (Bit 0)
.equ RSP_BRK, 0x0002 # SP_STATUS: Break (Bit 1)
.equ RSP_BSY, 0x0004 # SP_STATUS: DMA Busy (Bit 2)
.equ RSP_FUL, 0x0008 # SP_STATUS: DMA Full (Bit 3)
.equ RSP_IOF, 0x0010 # SP_STATUS: IO Full (Bit 4)
.equ RSP_STP, 0x0020 # SP_STATUS: Single Step (Bit 5)
.equ RSP_IOB, 0x0040 # SP_STATUS: Interrupt On Break (Bit 6)
.equ RSP_SG0, 0x0080 # SP_STATUS: Signal 0 Set (Bit 7)
.equ RSP_SG1, 0x0100 # SP_STATUS: Signal 1 Set (Bit 8)
.equ RSP_SG2, 0x0200 # SP_STATUS: Signal 2 Set (Bit 9)
.equ RSP_SG3, 0x0400 # SP_STATUS: Signal 3 Set (Bit 10)
.equ RSP_SG4, 0x0800 # SP_STATUS: Signal 4 Set (Bit 11)
.equ RSP_SG5, 0x1000 # SP_STATUS: Signal 5 Set (Bit 12)
.equ RSP_SG6, 0x2000 # SP_STATUS: Signal 6 Set (Bit 13)
.equ RSP_SG7, 0x4000 # SP_STATUS: Signal 7 Set (Bit 14)

# SP Status Write Flags:
.equ CLR_HLT, 0x0000001 # SP_STATUS: Clear Halt (Bit 0)
.equ SET_HLT, 0x0000002 # SP_STATUS: Set Halt (Bit 1)
.equ CLR_BRK, 0x0000004 # SP_STATUS: Clear Broke (Bit 2)
.equ CLR_INT, 0x0000008 # SP_STATUS: Clear Interrupt (Bit 3)
.equ SET_INT, 0x0000010 # SP_STATUS: Set Interrupt (Bit 4)
.equ CLR_STP, 0x0000020 # SP_STATUS: Clear Single Step (Bit 5)
.equ SET_STP, 0x0000040 # SP_STATUS: Set Single Step (Bit 6)
.equ CLR_IOB, 0x0000080 # SP_STATUS: Clear Interrupt On Break (Bit 7)
.equ SET_IOB, 0x0000100 # SP_STATUS: Set Interrupt On Break (Bit 8)
.equ CLR_SG0, 0x0000200 # SP_STATUS: Clear Signal 0 (Bit 9)
.equ SET_SG0, 0x0000400 # SP_STATUS: Set Signal 0 (Bit 10)
.equ CLR_SG1, 0x0000800 # SP_STATUS: Clear Signal 1 (Bit 11)
.equ SET_SG1, 0x0001000 # SP_STATUS: Set Signal 1 (Bit 12)
.equ CLR_SG2, 0x0002000 # SP_STATUS: Clear Signal 2 (Bit 13)
.equ SET_SG2, 0x0004000 # SP_STATUS: Set Signal 2 (Bit 14)
.equ CLR_SG3, 0x0008000 # SP_STATUS: Clear Signal 3 (Bit 15)
.equ SET_SG3, 0x0010000 # SP_STATUS: Set Signal 3 (Bit 16)
.equ CLR_SG4, 0x0020000 # SP_STATUS: Clear Signal 4 (Bit 17)
.equ SET_SG4, 0x0040000 # SP_STATUS: Set Signal 4 (Bit 18)
.equ CLR_SG5, 0x0080000 # SP_STATUS: Clear Signal 5 (Bit 19)
.equ SET_SG5, 0x0100000 # SP_STATUS: Set Signal 5 (Bit 20)
.equ CLR_SG6, 0x0200000 # SP_STATUS: Clear Signal 6 (Bit 21)
.equ SET_SG6, 0x0400000 # SP_STATUS: Set Signal 6 (Bit 22)
.equ CLR_SG7, 0x0800000 # SP_STATUS: Clear Signal 7 (Bit 23)
.equ SET_SG7, 0x1000000 # SP_STATUS: Set Signal 7 (Bit 24)

# CPU DMA
.macro DMASPRD start, end, dest # DMA Data Read DRAM->RSP MEM: Start Address, End Address, Destination RSP MEM Address
    lui $a0,SP_BASE # A0 = SP Base Register (0xA4040000)
    lui $t0,SP_MEM_BASE # T0 = SP Memory Base Register (0xA4000000)
    ori $t0,\dest&0x1FFF # T0 = SP Memory Address Offset (0xA4000000..0xA4001FFF 8KB)
    sw $t0,SP_MEM_ADDR($a0) # Store Memory Offset To SP Memory Address Register (0xA4040000)
    la $t0,\start&0x7FFFFFF # T0 = Aligned DRAM Physical RAM Offset (0x00000000..0x007FFFFF 8MB)
    sw $t0,SP_DRAM_ADDR($a0) # Store RAM Offset To SP DRAM Address Register (0xA4040004)
    la $t0,(\end-\start)-1 # T0 = Length Of DMA Transfer In Bytes - 1
    sw $t0,SP_RD_LEN($a0) # Store DMA Length To SP Read Length Register (0xA4040008)
.endm

.macro DMASPWR start, end, source # DMA Data Write RSP MEM->DRAM: Start Address, End Address, Source RSP MEM Address
    lui $a0,SP_BASE # A0 = SP Base Register (0xA4040000)
    lui $t0,SP_MEM_BASE # T0 = SP Memory Base Register (0xA4000000)
    ori $t0,\source&0x1FFF # T0 = SP Memory Address Offset (0xA4000000..0xA4001FFF 8KB)
    sw $t0,SP_MEM_ADDR($a0) # Store Memory Offset To SP Memory Address Register (0xA4040000)
    la $t0,\start&0x7FFFFFF # T0 = Aligned DRAM Physical RAM Offset (0x00000000..0x007FFFFF 8MB)
    sw $t0,SP_DRAM_ADDR($a0) # Store RAM Offset To SP DRAM Address Register (0xA4040004)
    la $t0,(\end-\start)-1 # T0 = Length Of DMA Transfer In Bytes - 1
    sw $t0,SP_WR_LEN($a0) # Store DMA Length To SP Write Length Register (0xA404000C)
.endm

# RSP DMA
.macro RSPDMASPRD start, end, dest # DMA Data Read DRAM->RSP MEM: Start Address, End Address, Destination RSP MEM Address
    li $a0,\dest&0x1FFF # A0 = SP Memory Address Offset (0xA4000000..0xA4001FFF 8KB)
    mtc0 $a0,c0 # Store Memory Offset To SP Memory Address Register (0xA4040000)
    la $a0,\start&0x7FFFFFF # A0 = Aligned DRAM Physical RAM Offset (0x00000000..0x007FFFFF 8MB)
    mtc0 $a0,c1 # Store RAM Offset To SP DRAM Address Register (0xA4040004)
    la $a0,(\end-\start)-1 # A0 = Length Of DMA Transfer In Bytes - 1
    mtc0 $a0,c2 # Store DMA Length To SP Read Length Register (0xA4040008)
.endm

.macro RSPDMASPWR start, end, source # DMA Data Write RSP MEM->DRAM: Start Address, End Address, Source RSP MEM Address
    li $a0,\source&0x1FFF # A0 = SP Memory Address Offset (0xA4000000..0xA4001FFF 8KB)
    mtc0 $a0,c0 # Store Memory Offset To SP Memory Address Register (0xA4040000)
    la $a0,\start&0x7FFFFFF # A0 = Aligned DRAM Physical RAM Offset (0x00000000..0x007FFFFF 8MB)
    mtc0 $a0,c1 # Store RAM Offset To SP DRAM Address Register (0xA4040004)
    la $a0,(\end-\start)-1 # A0 = Length Of DMA Transfer In Bytes - 1
    mtc0 $a0,c3 # Store DMA Length To SP Write Length Register (0xA404000C)
.endm

.macro RSPDPC start, end # Run DPC Command Buffer: Start Address, End Address
    la $a0,\start # A0 = DPC Command Start Address
    mtc0 $a0,c8 # Store DPC Command Start Address To DP Start Register (0xA4100000)
    addi $a0,\end-\start # A0 = DPC Command End Address
    mtc0 $a0,c9 # Store DPC Command End Address To DP End Register (0xA4100004)
.endm

# RSP CP2 Vector Operation Matrix Instructions (COP2):
.macro vmulf vd, vs, vt, element  # Vector Multiply Signed Fractions: VMULF VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x00 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMULF 0x00 (Bit 0..5)
.endm
.macro vmulu vd, vs, vt, element  # Vector Multiply Unsigned Fractions: VMULU VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x01 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMULU 0x01 (Bit 0..5)
.endm
.macro vrndp vd, vs, vt, element  # Vector DCT Round Positive: VRNDP VD,VS,VT[ELEMENT] (Reserved: MPEG DCT Rounding)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x02 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VRNDP 0x02 (Bit 0..5)
.endm
.macro vmulq vd, vs, vt, element  # Vector Multiply Integer: VMULQ VD,VS,VT[ELEMENT] (Reserved: MPEG Inverse Quantization)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x03 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMULQ 0x03 (Bit 0..5)
.endm
.macro vmudl vd, vs, vt, element  # Vector Multiply Low Partial Products: VMUDL VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x04 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMUDL 0x04 (Bit 0..5)
.endm
.macro vmudm vd, vs, vt, element  # Vector Multiply Mid Partial Products: VMUDM VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x05 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMUDM 0x05 (Bit 0..5)
.endm
.macro vmudn vd, vs, vt, element  # Vector Multiply Mid Partial Products: VMUDN VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x06 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMUDN 0x06 (Bit 0..5)
.endm
.macro vmudh vd, vs, vt, element  # Vector Multiply High Partial Products: VMUDH VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x07 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMUDH 0x07 (Bit 0..5)
.endm
.macro vmacf vd, vs, vt, element  # Vector Multiply Accumulate Signed Fractions: VMACF VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x08 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMACF 0x08 (Bit 0..5)
.endm
.macro vmacu vd, vs, vt, element  # Vector Multiply Accumulate Unsigned Fractions: VMACU VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x09 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMACU 0x09 (Bit 0..5)
.endm
.macro vrndn vd, vs, vt, element  # Vector DCT Round Negative: VRNDN VD,VS,VT[ELEMENT] (Reserved: MPEG DCT Rounding)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x0A # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VRNDN 0x0A (Bit 0..5)
.endm
.macro vmacq vd, vs, vt, element  # Vector Multiply Accumulate Integer: VMACQ VD,VS,VT[ELEMENT] (Reserved: MPEG Inverse Quantization)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x0B # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMACQ 0x0B (Bit 0..5)
.endm
.macro vmadl vd, vs, vt, element  # Vector Multiply Accumulate Low Partial Products: VMADL VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x0C # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMADL 0x0C (Bit 0..5)
.endm
.macro vmadm vd, vs, vt, element  # Vector Multiply Accumulate Mid Partial Products: VMADM VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x0D # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMADM 0x0D (Bit 0..5)
.endm
.macro vmadn vd, vs, vt, element  # Vector Multiply Accumulate Mid Partial Products: VMADN VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x0E # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMADN 0x0E (Bit 0..5)
.endm
.macro vmadh vd, vs, vt, element  # Vector Multiply Accumulate High Partial Products: VMADH VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x0F # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMADH 0x0F (Bit 0..5)
.endm
.macro vadd vd, vs, vt, element  # Vector Add Short Elements: VADD VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x10 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VADD 0x10 (Bit 0..5)
.endm
.macro vsub vd, vs, vt, element  # Vector Subtract Short Elements: VSUB VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x11 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VSUB 0x11 (Bit 0..5)
.endm
.macro vsut vd, vs, vt, element  # Vector Subtract Short Elements (VT-VS): VSUT VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x12 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VSUT 0x12 (Bit 0..5)
.endm
.macro vabs vd, vs, vt, element  # Vector Absolute Value Of Short Elements: VABS VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x13 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VABS 0x13 (Bit 0..5)
.endm
.macro vaddc vd, vs, vt, element  # Vector Add Short Elements With Carry: VADDC VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x14 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VADDC 0x14 (Bit 0..5)
.endm
.macro vsubc vd, vs, vt, element  # Vector Subtract Short Elements With Carry: VSUBC VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x15 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VSUBC 0x15 (Bit 0..5)
.endm
.macro vaddb vd, vs, vt, element  # Vector Add Byte Elements: VADDB VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x16 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VADDB 0x16 (Bit 0..5)
.endm
.macro vsubb vd, vs, vt, element  # Vector Subtract Byte Elements: VSUBB VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x17 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VSUBB 0x17 (Bit 0..5)
.endm
.macro vadcb vd, vs, vt, element  # Vector Add Byte Elements With Carry: VADCB VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x18 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VADCB 0x18 (Bit 0..5)
.endm
.macro vsucb vd, vs, vt, element  # Vector Subtract Byte Elements With Carry: VSUCB VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x19 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VSUCB 0x19 (Bit 0..5)
.endm
.macro vsad vd, vs, vt, element  # Vector SAD: VSAD VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x1A # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VSAD 0x1A (Bit 0..5)
.endm
.macro vsac vd, vs, vt, element  # Vector SAC: VSAC VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x1B # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VSAC 0x1B (Bit 0..5)
.endm
.macro vsum vd, vs, vt, element  # Vector SUM: VSUM VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x1C # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VSUM 0x1C (Bit 0..5)
.endm
.macro vsar vd, vs, vt, element  # Vector Accumulator Read: VSAR VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x1D # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VSAR 0x1D (Bit 0..5)
.endm
.macro vlt vd, vs, vt, element  # Vector Select Less Than: VLT VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x20 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VLT 0x20 (Bit 0..5)
.endm
.macro veq vd, vs, vt, element  # Vector Select Equal: VEQ VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x21 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VEQ 0x21 (Bit 0..5)
.endm
.macro vne vd, vs, vt, element  # Vector Select Not Equal: VNE VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x22 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VNE 0x22 (Bit 0..5)
.endm
.macro vge vd, vs, vt, element  # Vector Select Greater Than Or Equal: VGE VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x23 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VGE 0x23 (Bit 0..5)
.endm
.macro vcl vd, vs, vt, element  # Vector Select Clip Test Low: VCL VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x24 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VCL 0x24 (Bit 0..5)
.endm
.macro vch vd, vs, vt, element  # Vector Select Clip Test High: VCH VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x25 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VCH 0x25 (Bit 0..5)
.endm
.macro vcr vd, vs, vt, element  # Vector Select Clip Test Low (Single Precision): VCR VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x26 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VCR 0x26 (Bit 0..5)
.endm
.macro vmrg vd, vs, vt, element  # Vector Select Merge: VMRG VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x27 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMRG 0x27 (Bit 0..5)
.endm
.macro vand vd, vs, vt, element  # Vector Logical AND Short Elements: VAND VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x28 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VAND 0x28 (Bit 0..5)
.endm
.macro vnand vd, vs, vt, element  # Vector Logical NOT AND Short Elements: VNAND VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x29 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VNAND 0x29 (Bit 0..5)
.endm
.macro vor vd, vs, vt, element  # Vector Logical OR Short Elements: VOR VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x2A # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VOR 0x2A (Bit 0..5)
.endm
.macro vnor vd, vs, vt, element  # Vector Logical NOT OR Short Elements: VNOR VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x2B # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VNOR 0x2B (Bit 0..5)
.endm
.macro vxor vd, vs, vt, element  # Vector Logical Exclusive OR Short Elements: VXOR VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x2C # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VXOR 0x2C (Bit 0..5)
.endm
.macro vnxor vd, vs, vt, element  # Vector Logical NOT Exclusive OR Short Elements: VNXOR VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x2D # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VNXOR 0x2D (Bit 0..5)
.endm
.macro vrcp vd, vs, vt, element  # Vector Element Scalar Reciprocal (Single Precision): VRCP VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x30 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VRCP 0x30 (Bit 0..5)
.endm
.macro vrcpl vd, vs, vt, element  # Vector Element Scalar Reciprocal Low: VRCPL VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x31 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VRCPL 0x31 (Bit 0..5)
.endm
.macro vrcph vd, vs, vt, element  # Vector Element Scalar Reciprocal High: VRCPH VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x32 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VRCPH 0x32 (Bit 0..5)
.endm
.macro vmov vd, vs, vt, element  # Vector Element Scalar Move: VMOV VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x33 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VMOV 0x33 (Bit 0..5)
.endm
.macro vrsq vd, vs, vt, element  # Vector Element Scalar SQRT Reciprocal (Single Precision): VRSQ VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x34 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VRSQ 0x34 (Bit 0..5)
.endm
.macro vrsql vd, vs, vt, element  # Vector Element Scalar SQRT Reciprocal Low: VRSQL VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x35 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VRSQL 0x35 (Bit 0..5)
.endm
.macro vrsqh vd, vs, vt, element  # Vector Element Scalar SQRT Reciprocal High: VRSQH VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x36 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VRSQH 0x36 (Bit 0..5)
.endm
.macro vnop vd, vs, vt, element  # Vector Null Instruction: VNOP VD,VS,VT[ELEMENT]
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x37 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VNOP 0x37 (Bit 0..5)
.endm
.macro vextt vd, vs, vt, element  # Vector Extract Triple (5/5/5/1): VEXTT VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x38 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VEXTT 0x38 (Bit 0..5)
.endm
.macro vextq vd, vs, vt, element  # Vector Extract Quad (4/4/4/4): VEXTQ VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x39 # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VEXTQ 0x39 (Bit 0..5)
.endm
.macro vextn vd, vs, vt, element  # Vector Extract Nibble (4/4/4/4) (Sign Extended): VEXTN VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x3A # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VEXTN 0x3A (Bit 0..5)
.endm
.macro vinst vd, vs, vt, element  # Vector Insert Triple (5/5/5/1): VINST VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x3B # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VINST 0x3B (Bit 0..5)
.endm
.macro vinsq vd, vs, vt, element  # Vector Insert Quad (4/4/4/4): VINSQ VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x3C # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VINSQ 0x3C (Bit 0..5)
.endm
.macro vinsn vd, vs, vt, element  # Vector Insert Nibble (4/4/4/4) (Sign Extended): VINSN VD,VS,VT[ELEMENT] (Reserved)
# Word: Element (0..15), Source Vector 2 (0..31), Source Vector 1 (0..31), Destination Vector (0..31)
  .word 0x4A000000|(\element<<21)|(\vt<<16)|(\vs<<11)|(\vd<<6)|0x3D # Word: COP2 0x48 (Bit 26..31), Function Bit 1 (Bit 25), Element (Bit 21..25), Source Vector 2 (Bit 16..20), Source Vector 1 (Bit 11..15), Destination Vector (Bit 6..10), VINSN 0x3D (Bit 0..5)
.endm

# RSP CP2 Vector Load Instructions (LWC2):
.macro lbv vt, element, offset, base  # Load Byte To Vector: LBV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x00<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LBV 0x00 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro lsv vt, element, offset, base  # Load Short To Vector: LSV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x01<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LSV 0x01 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro llv vt, element, offset, base  # Load Long To Vector: LLV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x02<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LLV 0x02 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro ldv vt, element, offset, base  # Load Double To Vector: LDV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x03<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LDV 0x03 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro lqv vt, element, offset, base  # Load Quad To Vector: LQV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x04<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LQV 0x04 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro lrv vt, element, offset, base  # Load Rest To Vector: LRV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x05<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LRV 0x05 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro lpv vt, element, offset, base  # Load Packed Signed To Vector: LPV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x06<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LPV 0x06 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro luv vt, element, offset, base  # Load Packed Unsigned To Vector: LUV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x07<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LUV 0x07 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro lhv vt, element, offset, base  # Load Half Bytes To Vector: LHV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x08<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LHV 0x08 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro lfv vt, element, offset, base  # Load Fourth Bytes To Vector: LFV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x09<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LFV 0x09 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro lwv vt, element, offset, base  # Load Transposed Wrapped Bytes To Vector: LWV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x0A<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LWV 0x0A (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro ltv vt, element, offset, base  # Load Transposed Bytes To Vector: LTV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xC8000000|(\base<<21)|(\vt<<16)|(0x0B<<11)|(\element<<7)|\offset # Word: LWC2 0xC8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), LTV 0x0B (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm

# RSP CP2 Vector Store Instructions (SWC2):
.macro sbv vt, element, offset, base  # Store Byte From Vector: SBV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x00<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SBV 0x00 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro ssv vt, element, offset, base  # Store Short From Vector: SSV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x01<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SSV 0x01 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro slv vt, element, offset, base  # Store Long From Vector: SLV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x02<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SLV 0x02 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro sdv vt, element, offset, base  # Store Double From Vector: SDV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x03<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SDV 0x03 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro sqv vt, element, offset, base  # Store Quad From Vector: SQV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x04<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SQV 0x04 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro srv vt, element, offset, base  # Store Rest From Vector: SRV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x05<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SRV 0x05 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro spv vt, element, offset, base  # Store Packed Signed From Vector: SPV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x06<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SPV 0x06 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro suv vt, element, offset, base  # Store Packed Unsigned From Vector: SUV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x07<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SUV 0x07 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro shv vt, element, offset, base  # Store Half Bytes From Vector: SHV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x08<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SHV 0x08 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro sfv vt, element, offset, base  # Store Fourth Bytes From Vector: SFV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x09<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SFV 0x09 (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro swv vt, element, offset, base  # Store Transposed Wrapped Bytes From Vector: SWV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x0A<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), SWV 0x0A (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
.macro stv vt, element, offset, base  # Store Transposed Bytes From Vector: STV VT[ELEMENT],$OFFSET(BASE)
# Word: Base Register (0..31), Destination Vector (0..31), Destination Element (0..15), Offset (0x00..0x3F)
  .word 0xE8000000|(\base<<21)|(\vt<<16)|(0x0B<<11)|(\element<<7)|\offset # Word: SWC2 0xE8 (Bit 26..31), Base (Bit 21..25), Vector (Bit 16..20), STV 0x0B (Bit 11..15), Element (Bit 7..10), Offset (Bit 0..5)
.endm
# vim:ft=mips
