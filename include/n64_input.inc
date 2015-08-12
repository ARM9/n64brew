//===========
// N64 Input
//===========
.equ JOY_CRIGHT, 0x1 // PIF HWORD: CAMERA RIGHT
.equ JOY_CLEFT,  0x2 // PIF HWORD: CAMERA LEFT
.equ JOY_CDOWN,  0x4 // PIF HWORD: CAMERA DOWN
.equ JOY_CUP,    0x8 // PIF HWORD: CAMERA UP
.equ JOY_R,      0x10 // PIF HWORD: R (PAN RIGHT)
.equ JOY_L,      0x20 // PIF HWORD: L (PAN LEFT)
.equ JOY_RIGHT,  0x100 // PIF HWORD: RIGHT
.equ JOY_LEFT,   0x200 // PIF HWORD: LEFT
.equ JOY_DOWN,   0x400 // PIF HWORD: DOWN
.equ JOY_UP,     0x800 // PIF HWORD: UP
.equ JOY_START,  0x1000 // PIF HWORD: START
.equ JOY_Z,      0x2000 // PIF HWORD: Z
.equ JOY_B,      0x4000 // PIF HWORD: B
.equ JOY_A,      0x8000 // PIF HWORD: A

.macro InitController PIF 
  lui $a0,SI_BASE // A0 = SI Base Register ($A4800000)
  la $a1,\PIF // A1 = PIF1 Offset
  sw $a1,SI_DRAM_ADDR($a0) // Store PIF1 To SI_DRAM_ADDR ($A4800000)
  la $a1,((PIF_BASE<<16)|PIF_RAM) // A1 = PIF_RAM: JoyChannel ($BFC007C0)
  sw $a1,SI_PIF_ADDR_WR64B($a0) // 64 Byte Write DRAM -> PIF ($A4800010)
.endm

.macro ReadController PIF 
  lui $a0,PIF_BASE // A0 = PIF Base Register ($BFC00000)
  lui $a1,SI_BASE // A1 = SI Base Register ($A4800000)
  la $a2,\PIF // A2 = PIF2 Offset
  sw $a2,SI_DRAM_ADDR($a1) // Store PIF2 To SI_DRAM_ADDR ($A4800000)
  ori $a2,$a0,PIF_RAM // A2 = PIF_RAM: JoyChannel ($BFC007C0)
  sw $a2,SI_PIF_ADDR_RD64B($a1) // 64 Byte Read PIF -> DRAM ($A4800004)
  lhu $t0,PIF_HWORD($a0) // T0 = Buttons ($BFC007C4)
  lb $t1,PIF_XBYTE($a0) // T1 = Analog X ($BFC007C6)
  lb $t2,PIF_YBYTE($a0) // T2 = Analog Y ($BFC007C7)
.endm
// vim:ft=mips
