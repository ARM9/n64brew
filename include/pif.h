#ifndef LIBN64_PIF_H
#define LIBN64_PIF_H

#include <mmio.h>

#define PIF_BASE    0xBFC00000 // $1FC00000..$1FC007BF PIF Base Register
#define PIF_ROM     IO_8(PIF_BASE,0x000) // $1FC00000..$1FC007BF PIF: Boot ROM
#define PIF_RAM     IO_8(PIF_BASE,0x7C0) // $1FC007C0..$1FC007FF PIF: RAM (JoyChannel)
#define PIF_HWORD   IO_16(PIF_BASE,0x7C4) // $1FC007C4..$1FC007C5 PIF: HWORD
#define PIF_XBYTE   IO_8(PIF_BASE,0x7C6) // $1FC007C6 PIF: Analog X Byte
#define PIF_YBYTE   IO_8(PIF_BASE,0x7C7) // $1FC007C7 PIF: Analog Y Byte

#endif
