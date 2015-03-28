#=============
# N64 Include
#=============
# Memory Map
.equ RDRAM, 0xA000 # $00000000..$003FFFFF RDRAM Memory 4MB ($00000000..$007FFFFF 8MB With Expansion Pak)

.equ RDRAM_BASE,       0xA3F0 # $03F00000..$03F00027 RDRAM Base Register
.equ RDRAM_DEVICE_TYPE,  0x00 # $03F00000..$03F00003 RDRAM: Device Type Register
.equ RDRAM_DEVICE_ID,    0x04 # $03F00004..$03F00007 RDRAM: Device ID Register
.equ RDRAM_DELAY,        0x08 # $03F00008..$03F0000B RDRAM: Delay Register
.equ RDRAM_MODE,         0x0C # $03F0000C..$03F0000F RDRAM: Mode Register
.equ RDRAM_REF_INTERVAL, 0x10 # $03F00010..$03F00013 RDRAM: Ref Interval Register
.equ RDRAM_REF_ROW,      0x14 # $03F00014..$03F00017 RDRAM: Ref Row Register
.equ RDRAM_RAS_INTERVAL, 0x18 # $03F00018..$03F0001B RDRAM: Ras Interval Register
.equ RDRAM_MIN_INTERVAL, 0x1C # $03F0001C..$03F0001F RDRAM: Minimum Interval Register
.equ RDRAM_ADDR_SELECT,  0x20 # $03F00020..$03F00023 RDRAM: Address Select Register
.equ RDRAM_DEVICE_MANUF, 0x24 # $03F00024..$03F00027 RDRAM: Device Manufacturer Register

.equ SP_MEM_BASE, 0xA400 # $04000000..$04000FFF SP MEM Base Register
.equ SP_DMEM,     0x0000 # $04000000..$04000FFF SP: RSP DMEM (4096 Bytes)
.equ SP_IMEM,     0x1000 # $04001000..$04001FFF SP: RSP IMEM (4096 Bytes)

.equ SP_BASE,    0xA404 # $04040000..$0404001F SP Base Register
.equ SP_MEM_ADDR,  0x00 # $04040000..$04040003 SP: Master, SP Memory Address Register
.equ SP_DRAM_ADDR, 0x04 # $04040004..$04040007 SP: Slave, SP DRAM DMA Address Register
.equ SP_RD_LEN,    0x08 # $04040008..$0404000B SP: Read DMA Length Register
.equ SP_WR_LEN,    0x0C # $0404000C..$0404000F SP: Write DMA Length Register
.equ SP_STATUS,    0x10 # $04040010..$04040013 SP: Status Register
.equ SP_DMA_FULL,  0x14 # $04040014..$04040017 SP: DMA Full Register
.equ SP_DMA_BUSY,  0x18 # $04040018..$0404001B SP: DMA Busy Register
.equ SP_SEMAPHORE, 0x1C # $0404001C..$0404001F SP: Semaphore Register

.equ SP_PC_BASE,  0xA408 # $04080000..$04080007 SP PC Base Register
.equ SP_PC,         0x00 # $04080000..$04080003 SP: PC Register
.equ SP_IBIST_REG,  0x04 # $04080004..$04080007 SP: IMEM BIST Register

.equ DPC_BASE,   0xA410 # $04100000..$0410001F DP Command (DPC) Base Register
.equ DPC_START,    0x00 # $04100000..$04100003 DPC: CMD DMA Start Register
.equ DPC_END,      0x04 # $04100004..$04100007 DPC: CMD DMA End Register
.equ DPC_CURRENT,  0x08 # $04100008..$0410000B DPC: CMD DMA Current Register
.equ DPC_STATUS,   0x0C # $0410000C..$0410000F DPC: CMD Status Register
.equ DPC_CLOCK,    0x10 # $04100010..$04100013 DPC: Clock Counter Register
.equ DPC_BUFBUSY,  0x14 # $04100014..$04100017 DPC: Buffer Busy Counter Register
.equ DPC_PIPEBUSY, 0x18 # $04100018..$0410001B DPC: Pipe Busy Counter Register
.equ DPC_TMEM,     0x1C # $0410001C..$0410001F DPC: TMEM Load Counter Register

.equ DPS_BASE,       0xA420 # $04200000..$0420000F DP Span (DPS) Base Register
.equ DPS_TBIST,        0x00 # $04200000..$04200003 DPS: Tmem Bist Register
.equ DPS_TEST_MODE,    0x04 # $04200004..$04200007 DPS: Span Test Mode Register
.equ DPS_BUFTEST_ADDR, 0x08 # $04200008..$0420000B DPS: Span Buffer Test Address Register
.equ DPS_BUFTEST_DATA, 0x0C # $0420000C..$0420000F DPS: Span Buffer Test Data Register

.equ MI_BASE,    0xA430 # $04300000..$0430000F MIPS Interface (MI) Base Register
.equ MI_INIT_MODE, 0x00 # $04300000..$04300003 MI: Init Mode Register
.equ MI_VERSION,   0x04 # $04300004..$04300007 MI: Version Register
.equ MI_INTR,      0x08 # $04300008..$0430000B MI: Interrupt Register
.equ MI_INTR_MASK, 0x0C # $0430000C..$0430000F MI: Interrupt Mask Register

.equ VI_BASE,         0xA440 # $04400000..$04400037 Video Interface (VI) Base Register
.equ VI_STATUS,         0x00 # $04400000..$04400003 VI: Status/Control Register
.equ VI_ORIGIN,         0x04 # $04400004..$04400007 VI: Origin Register
.equ VI_WIDTH,          0x08 # $04400008..$0440000B VI: Width Register
.equ VI_V_INTR,         0x0C # $0440000C..$0440000F VI: Vertical Interrupt Register
.equ VI_V_CURRENT_LINE, 0x10 # $04400010..$04400013 VI: Current Vertical Line Register
.equ VI_TIMING,         0x14 # $04400014..$04400017 VI: Video Timing Register
.equ VI_V_SYNC,         0x18 # $04400018..$0440001B VI: Vertical Sync Register
.equ VI_H_SYNC,         0x1C # $0440001C..$0440001F VI: Horizontal Sync Register
.equ VI_H_SYNC_LEAP,    0x20 # $04400020..$04400023 VI: Horizontal Sync Leap Register
.equ VI_H_VIDEO,        0x24 # $04400024..$04400027 VI: Horizontal Video Register
.equ VI_V_VIDEO,        0x28 # $04400028..$0440002B VI: Vertical Video Register
.equ VI_V_BURST,        0x2C # $0440002C..$0440002F VI: Vertical Burst Register
.equ VI_X_SCALE,        0x30 # $04400030..$04400033 VI: X-Scale Register
.equ VI_Y_SCALE,        0x34 # $04400034..$04400037 VI: Y-Scale Register

.equ AI_BASE,    0xA450 # $04500000..$04500017 Audio Interface (AI) Base Register
.equ AI_DRAM_ADDR, 0x00 # $04500000..$04500003 AI: DRAM Address Register
.equ AI_LEN,       0x04 # $04500004..$04500007 AI: Length Register
.equ AI_CONTROL,   0x08 # $04500008..$0450000B AI: Control Register
.equ AI_STATUS,    0x0C # $0450000C..$0450000F AI: Status Register
.equ AI_DACRATE,   0x10 # $04500010..$04500013 AI: DAC Sample Period Register
.equ AI_BITRATE,   0x14 # $04500014..$04500017 AI: Bit Rate Register

.equ PI_BASE,       0xA460 # $04600000..$04600033 Peripheral Interface (PI) Base Register
.equ PI_DRAM_ADDR,    0x00 # $04600000..$04600003 PI: DRAM Address Register
.equ PI_CART_ADDR,    0x04 # $04600004..$04600007 PI: Pbus (Cartridge) Address Register
.equ PI_RD_LEN,       0x08 # $04600008..$0460000B PI: Read Length Register
.equ PI_WR_LEN,       0x0C # $0460000C..$0460000F PI: Write length register
.equ PI_STATUS,       0x10 # $04600010..$04600013 PI: Status Register
.equ PI_BSD_DOM1_LAT, 0x14 # $04600014..$04600017 PI: Domain 1 Latency Register
.equ PI_BSD_DOM1_PWD, 0x18 # $04600018..$0460001B PI: Domain 1 Pulse Width Register
.equ PI_BSD_DOM1_PGS, 0x1C # $0460001C..$0460001F PI: Domain 1 Page Size Register
.equ PI_BSD_DOM1_RLS, 0x20 # $04600020..$04600023 PI: Domain 1 Release Register
.equ PI_BSD_DOM2_LAT, 0x24 # $04600024..$04600027 PI: Domain 2 Latency Register
.equ PI_BSD_DOM2_PWD, 0x28 # $04600028..$0460002B PI: Domain 2 Pulse Width Register
.equ PI_BSD_DOM2_PGS, 0x2C # $0460002C..$0460002F PI: Domain 2 Page Size Register
.equ PI_BSD_DOM2_RLS, 0x30 # $04600030..$04600033 PI: Domain 2 Release Register

.equ RI_BASE,       0xA470 # $04700000..$0470001F RDRAM Interface (RI) Base Register
.equ RI_MODE,         0x00 # $04700000..$04700003 RI: Mode Register
.equ RI_CONFIG,       0x04 # $04700004..$04700007 RI: Config Register
.equ RI_CURRENT_LOAD, 0x08 # $04700008..$0470000B RI: Current Load Register
.equ RI_SELECT,       0x0C # $0470000C..$0470000F RI: Select Register
.equ RI_REFRESH,      0x10 # $04700010..$04700013 RI: Refresh Register
.equ RI_LATENCY,      0x14 # $04700014..$04700017 RI: Latency Register
.equ RI_RERROR,       0x18 # $04700018..$0470001B RI: Read Error Register
.equ RI_WERROR,       0x1C # $0470001C..$0470001F RI: Write Error Register

.equ SI_BASE,         0xA480 # $04800000..$0480001B Serial Interface (SI) Base Register
.equ SI_DRAM_ADDR,      0x00 # $04800000..$04800003 SI: DRAM Address Register
.equ SI_PIF_ADDR_RD64B, 0x04 # $04800004..$04800007 SI: Address Read 64B Register
#*RESERVED*:       equ $08 # $04800008..$0480000B SI: Reserved Register
#*RESERVED*:       equ $0C # $0480000C..$0480000F SI: Reserved Register
.equ SI_PIF_ADDR_WR64B, 0x10 # $04800010..$04800013 SI: Address Write 64B Register
#*RESERVED*:       equ $14 # $04800014..$04800017 SI: Reserved Register
.equ SI_STATUS,         0x18 # $04800018..$0480001B SI: Status Register

.equ CART_DOM2_ADDR1, 0xA500 # $05000000..$0507FFFF Cartridge Domain 2(Address 1) SRAM
.equ CART_DOM1_ADDR1, 0xA600 # $06000000..$07FFFFFF Cartridge Domain 1(Address 1) 64DD
.equ CART_DOM1_ADDR2, 0xB000 # $10000000..$18000803 Cartridge Domain 1(Address 2) ROM

.equ PIF_BASE, 0xBFC0 # $1FC00000..$1FC007BF PIF Base Register
.equ PIF_ROM,   0x000 # $1FC00000..$1FC007BF PIF: Boot ROM
.equ PIF_RAM,   0x7C0 # $1FC007C0..$1FC007FF PIF: RAM (JoyChannel)
.equ PIF_HWORD, 0x7C4 # $1FC007C4..$1FC007C5 PIF: HWORD
.equ PIF_XBYTE, 0x7C6 # $1FC007C6 PIF: Analog X Byte
.equ PIF_YBYTE, 0x7C7 # $1FC007C7 PIF: Analog Y Byte

.equ VI_NTSC_CLOCK, 48681812 # NTSC: Hz = 48.681812 MHz
.equ VI_PAL_CLOCK,  49656530 # PAL:  Hz = 49.656530 MHz
.equ VI_MPAL_CLOCK, 48628316 # MPAL: Hz = 48.628316 MHz

.macro N64_INIT  # Initialise N64 (Stop N64 From Crashing 5 Seconds After Boot)
  lui $a0,PIF_BASE # A0 = PIF Base Register ($BFC00000)
  li $t0,8
  sw $t0,(PIF_RAM+0x3C)($a0)
.endm

.macro DMA start, end, dest  # DMA Data Copy Cart->DRAM: Start Cart Address, End Cart Address, Destination DRAM Address
  lui $a0,PI_BASE # A0 = PI Base Register ($A4600000)
  DMABusy\@:
    lb $t0,PI_STATUS($a0) # T0 = Byte From PI Status Register ($A4600010)
    sync # Sync Load
    andi $t0,3 # AND PI Status With 3
    bnez $t0,DMABusy\@ # IF TRUE DMA Is Busy
    nop # Delay Slot

    la $t0,\dest&0x7FFFFF # T0 = Aligned DRAM Physical RAM Offset ($00000000..$007FFFFF 8MB)
    sw $t0,PI_DRAM_ADDR($a0) # Store RAM Offset To PI DRAM Address Register ($A4600000)
    la $t0,0x10000000|(start&0x3FFFFFF) # T0 = Aligned Cart Physical ROM Offset ($10000000..$13FFFFFF 64MB)
    sw $t0,PI_CART_ADDR($a0) # Store ROM Offset To PI Cart Address Register ($A4600004)
    la $t0,(\end-\start)-1 # T0 = Length Of DMA Transfer In Bytes - 1
    sw $t0,PI_WR_LEN($a0) # Store DMA Length To PI Write Length Register ($A460000C)
.endm
# vim:ft=mips
