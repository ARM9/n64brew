#ifndef LIBN64_RDRAM_H
#define LIBN64_RDRAM_H

#include <mmio.h>

#define RDRAM   0xA0000000 // $00000000..$003FFFFF RDRAM Memory 4MB ($00000000..$007FFFFF 8MB With Expansion Pak)

#define RDRAM_BASE  0xA3F00000 // $03F00000..$03F00027 RDRAM Base Register
#define RDRAM_DEVICE_TYPE   IO_32(RDRAM_BASE,0x00 // $03F00000..$03F00003 RDRAM: Device Type Register
#define RDRAM_DEVICE_ID     IO_32(RDRAM_BASE,0x04 // $03F00004..$03F00007 RDRAM: Device ID Register
#define RDRAM_DELAY         IO_32(RDRAM_BASE,0x08) // $03F00008..$03F0000B RDRAM: Delay Register
#define RDRAM_MODE          IO_32(RDRAM_BASE,0x0C) // $03F0000C..$03F0000F RDRAM: Mode Register
#define RDRAM_REF_INTERVAL  IO_32(RDRAM_BASE,0x10) // $03F00010..$03F00013 RDRAM: Ref Interval Register
#define RDRAM_REF_ROW       IO_32(RDRAM_BASE,0x14) // $03F00014..$03F00017 RDRAM: Ref Row Register
#define RDRAM_RAS_INTERVAL  IO_32(RDRAM_BASE,0x18) // $03F00018..$03F0001B RDRAM: Ras Interval Register
#define RDRAM_MIN_INTERVAL  IO_32(RDRAM_BASE,0x1C) // $03F0001C..$03F0001F RDRAM: Minimum Interval Register
#define RDRAM_ADDR_SELECT   IO_32(RDRAM_BASE,0x20) // $03F00020..$03F00023 RDRAM: Address Select Register
#define RDRAM_DEVICE_MANUF  IO_32(RDRAM_BASE,0x24) // $03F00024..$03F00027 RDRAM: Device Manufacturer Register

#define RI_BASE 0xA4700000 // $04700000..$0470001F RDRAM Interface (RI) Base Register
#define RI_MODE         IO_32(RI_BASE,0x00) // $04700000..$04700003 RI: Mode Register
#define RI_CONFIG       IO_32(RI_BASE,0x04) // $04700004..$04700007 RI: Config Register
#define RI_CURRENT_LOAD IO_32(RI_BASE,0x08) // $04700008..$0470000B RI: Current Load Register
#define RI_SELECT       IO_32(RI_BASE,0x0C) // $0470000C..$0470000F RI: Select Register
#define RI_REFRESH      IO_32(RI_BASE,0x10) // $04700010..$04700013 RI: Refresh Register
#define RI_LATENCY      IO_32(RI_BASE,0x14) // $04700014..$04700017 RI: Latency Register
#define RI_RERROR       IO_32(RI_BASE,0x18) // $04700018..$0470001B RI: Read Error Register
#define RI_WERROR       IO_32(RI_BASE,0x1C) // $0470001C..$0470001F RI: Write Error Register

#endif
