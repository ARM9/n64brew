#ifndef LIBN64_SI_H
#define LIBN64_SI_H

#include <bitfield.h>

#define SI_BASE 0xA4800000 // $04800000..$0480001B Serial Interface (SI) Base Register
#define SI_DRAM_ADDR IO_32(SI_BASE,0x00) // $04800000..$04800003 SI: DRAM Address Register
#define SI_PIF_ADDR_RD64B IO_32(SI_BASE,0x04) // $04800004..$04800007 SI: Address Read 64B Register
//*RESERVED*:      #define $08 // $04800008..$0480000B SI: Reserved Register
//*RESERVED*:      #define $0C // $0480000C..$0480000F SI: Reserved Register
#define SI_PIF_ADDR_WR64B IO_32(SI_BASE,0x10) // $04800010..$04800013 SI: Address Write 64B Register
//*RESERVED*:      #define $14 // $04800014..$04800017 SI: Reserved Register
#define SI_STATUS IO_32(SI_BASE,0x18) // $04800018..$0480001B SI: Status Register

#endif
