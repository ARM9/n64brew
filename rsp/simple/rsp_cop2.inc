#ifndef RSP_COP2_INC
#define RSP_COP2_INC

#define FMT_LV(op, vt, elem, offset, base) \
	.word 0xC8000000 | (((base) & 31)<<21) | (((vt) & 31)<<16) | (((op) & 31)<<11) | (((elem) & 15)<<7) | ((offset) & 127)

#define FMT_SV(op, vt, elem, offset, base) \
	.word 0xE8000000 | (((base) & 31)<<21) | (((vt) & 31)<<16) | (((op) & 31)<<11) | (((elem) & 15)<<7) | ((offset) & 127)

#define FMT_COP2_3B(op, vd, vs, vt, e) \
	.word 0x4A000000 | (((e) & 15)<<21) | (((vt) & 31)<<16) | (((vs) & 31)<<11) | (((vd) & 31)<<6) | ((op) & 63)

#define FMT_COP2_3D(op, vd, de, vt, e) \
	.word 0x4A000000 | (((e) & 15)<<21) | (((vt) & 31)<<16) | (((de) & 31)<<11) | (((vd) & 31)<<6) | ((op) & 63)

.macro MFC2 rt, rd, elem
    .word 0x48000000 | (((\rt) & 31)<<16) | (((\rd) & 31)<<11) | (((\elem) & 15)<<7)
.endm

.macro MTC2 rt, rd, elem
    .word 0x48800000 | (((\rt) & 31)<<16) | (((\rd) & 31)<<11) | (((\elem) & 15)<<7)
.endm

// TODO CTC2, CFC2

.macro lhv vt, offset, base
 FMT_LV( 8, \vt, 0, \offset, \base)
.endm
.macro lpv vt, offset, base
 FMT_LV( 6, \vt, 0, \offset, \base)
.endm
.macro lqv vt, offset, base
 FMT_LV( 4, \vt, 0, \offset, \base)
.endm
.macro lrv vt, offset, base
 FMT_LV( 5, \vt, 0, \offset, \base)
.endm
.macro luv vt, offset, base
 FMT_LV( 7, \vt, 0, \offset, \base)
.endm

.macro lbv vt, elem, offset, base
 FMT_LV( 0, \vt, \elem, \offset, \base)
.endm
.macro ldv vt, elem, offset, base
 FMT_LV( 3, \vt, \elem, (\offset)>>3, \base)
.endm
.macro lfv vt, elem, offset, base
 FMT_LV( 9, \vt, \elem, \offset, \base)
.endm
.macro llv vt, elem, offset, base
 FMT_LV( 2, \vt, \elem, (\offset)>>2, \base)
.endm
.macro lsv vt, elem, offset, base
 FMT_LV( 1, \vt, \elem, (\offset)>>1, \base)
.endm
.macro ltv vt, elem, offset, base
 FMT_LV(11, \vt, \elem, \offset, \base)
.endm
//define LWV(vt, elem, offset, base) FMT_LV(10, vt, elem, offset, base)

.macro shv vt, offset, base
 FMT_SV( 8, \vt, 0, \offset, \base)
.endm
.macro spv vt, offset, base
 FMT_SV( 6, \vt, 0, \offset, \base)
.endm
.macro sqv vt, offset, base
 FMT_SV( 4, \vt, 0, \offset, \base)
.endm
.macro srv vt, offset, base
 FMT_SV( 5, \vt, 0, \offset, \base)
.endm
.macro suv vt, offset, base
 FMT_SV( 7, \vt, 0, \offset, \base)
.endm

.macro sbv vt, elem, offset, base
 FMT_SV( 0, \vt, \elem, \offset, \base)
.endm
.macro sdv vt, elem, offset, base
 FMT_SV( 3, \vt, \elem, (\offset)>>3, \base)
.endm
.macro sfv vt, elem, offset, base
 FMT_SV( 9, \vt, \elem, \offset, \base)
.endm
.macro slv vt, elem, offset, base
 FMT_SV( 2, \vt, \elem, (\offset)>>2, \base)
.endm
.macro ssv vt, elem, offset, base
 FMT_SV( 1, \vt, \elem, (\offset)>>1, \base)
.endm
.macro stv vt, elem, offset, base
 FMT_SV(11, \vt, \elem, \offset, \base)
.endm
.macro swv vt, elem, offset, base
 FMT_SV(10, \vt, \elem, \offset, \base)
.endm

.macro vabs vd, vs, vt, e=0
 FMT_COP2_3B(19, \vd, \vs, \vt, \e)
.endm
.macro vadd vd, vs, vt, e=0
 FMT_COP2_3B(16, \vd, \vs, \vt, \e)
.endm
.macro vaddc vd, vs, vt, e=0
 FMT_COP2_3B(20, \vd, \vs, \vt, \e)
.endm
.macro vand vd, vs, vt, e=0
 FMT_COP2_3B(40, \vd, \vs, \vt, \e)
.endm
.macro vch vd, vs, vt, e=0
 FMT_COP2_3B(37, \vd, \vs, \vt, \e)
.endm
.macro vcl vd, vs, vt, e=0
 FMT_COP2_3B(36, \vd, \vs, \vt, \e)
.endm
.macro vcr vd, vs, vt, e=0
 FMT_COP2_3B(38, \vd, \vs, \vt, \e)
.endm
.macro veq vd, vs, vt, e=0
 FMT_COP2_3B(33, \vd, \vs, \vt, \e)
.endm
.macro vge vd, vs, vt, e=0
 FMT_COP2_3B(35, \vd, \vs, \vt, \e)
.endm
.macro vlt vd, vs, vt, e=0
 FMT_COP2_3B(32, \vd, \vs, \vt, \e)
.endm
.macro vmacf vd, vs, vt, e=0
 FMT_COP2_3B(8, \vd, \vs, \vt, \e)
.endm
.macro vmacq vd, vs, vt, e=0
 FMT_COP2_3B(11, \vd, \vs, \vt, \e)
.endm
.macro vmacu vd, vs, vt, e=0
 FMT_COP2_3B(9, \vd, \vs, \vt, \e)
.endm
.macro vmadh vd, vs, vt, e=0
 FMT_COP2_3B(15, \vd, \vs, \vt, \e)
.endm
.macro vmadl vd, vs, vt, e=0
 FMT_COP2_3B(12, \vd, \vs, \vt, \e)
.endm
.macro vmadm vd, vs, vt, e=0
 FMT_COP2_3B(13, \vd, \vs, \vt, \e)
.endm
.macro vmadn vd, vs, vt, e=0
 FMT_COP2_3B(14, \vd, \vs, \vt, \e)
.endm
.macro vmov vd, de, vt, e=0
 FMT_COP2_3D(51, \vd, \de, \vt, \e)
.endm
.macro vmrg vd, vs, vt, e=0
 FMT_COP2_3B(39, \vd, \vs, \vt, \e)
.endm
.macro vmudh vd, vs, vt, e=0
 FMT_COP2_3B(7, \vd, \vs, \vt, \e)
.endm
.macro vmudl vd, vs, vt, e=0
 FMT_COP2_3B(4, \vd, \vs, \vt, \e)
.endm
.macro vmudm vd, vs, vt, e=0
 FMT_COP2_3B(5, \vd, \vs, \vt, \e)
.endm
.macro vmudn vd, vs, vt, e=0
 FMT_COP2_3B(6, \vd, \vs, \vt, \e)
.endm
.macro vmulf vd, vs, vt, e=0
 FMT_COP2_3B(0, \vd, \vs, \vt, \e)
.endm
.macro vmulq vd, vs, vt, e=0
 FMT_COP2_3B(3, \vd, \vs, \vt, \e)
.endm
.macro vmulu vd, vs, vt, e=0
 FMT_COP2_3B(1, \vd, \vs, \vt, \e)
.endm
.macro vnand vd, vs, vt, e=0
 FMT_COP2_3B(41, \vd, \vs, \vt, \e)
.endm
.macro vne vd, vs, vt, e=0
 FMT_COP2_3B(34, \vd, \vs, \vt, \e)
.endm
.macro vnop vd, vs, vt, e=0
 FMT_COP2_3B(56, \vd, \vs, \vt, \e)
.endm
.macro vnor vd, vs, vt, e=0
 FMT_COP2_3B(43, \vd, \vs, \vt, \e)
.endm
.macro vnxor vd, vs, vt, e=0
 FMT_COP2_3B(45, \vd, \vs, \vt, \e)
.endm
.macro vor vd, vs, vt, e=0
 FMT_COP2_3B(42, \vd, \vs, \vt, \e)
.endm
.macro vrcp vd, de, vt, e=0
 FMT_COP2_3D(48, \vd, \de, \vt, \e)
.endm
.macro vrcph vd, de, vt, e=0
 FMT_COP2_3D(50, \vd, \de, \vt, \e)
.endm
.macro vrcpl vd, de, vt, e=0
 FMT_COP2_3D(49, \vd, \de, \vt, \e)
.endm
.macro vrndn vd, vs, vt, e=0
 FMT_COP2_3B(10, \vd, \vs, \vt, \e)
.endm
.macro vrndp vd, vs, vt, e=0
 FMT_COP2_3B(2, \vd, \vs, \vt, \e)
.endm
.macro vrsq vd, de, vt, e=0
 FMT_COP2_3D(52, \vd, \de, \vt, \e)
.endm
.macro vrsqh vd, de, vt, e=0
 FMT_COP2_3D(54, \vd, \de, \vt, \e)
.endm
.macro vrsql vd, de, vt, e=0
 FMT_COP2_3D(53, \vd, \de, \vt, \e)
.endm
.macro vsar vd, vs, vt, e=0
 FMT_COP2_3B(29, \vd, \vs, \vt, \e)
.endm
.macro vsub vd, vs, vt, e=0
 FMT_COP2_3B(17, \vd, \vs, \vt, \e)
.endm
.macro vsubc vd, vs, vt, e=0
 FMT_COP2_3B(21, \vd, \vs, \vt, \e)
.endm
.macro vxor vd, vs, vt, e=0
 FMT_COP2_3B(44, \vd, \vs, \vt, \e)
.endm

// gpr for macros that can't take $0
#define R_ZERO 0
#define R_AT 1
#define R_V0 2
#define R_V1 3
#define R_A0 4
#define R_A1 5
#define R_A2 6
#define R_A3 7
#define R_T0 8
#define R_T1 9
#define R_T2 10
#define R_T3 11
#define R_T4 12
#define R_T5 13
#define R_T6 14
#define R_T7 15
#define R_S0 16
#define R_S1 17
#define R_S2 18
#define R_S3 19
#define R_S4 20
#define R_S5 21
#define R_S6 22
#define R_S7 23
#define R_T8 24
#define R_T9 25
#define R_K0 26
#define R_K1 27
#define R_GP 28
#define R_SP 29

#define R_S8 30

// RSP COP2 Vector Registers
#define v0 0
#define v1 1
#define v2 2
#define v3 3
#define v4 4
#define v5 5
#define v6 6
#define v7 7
#define v8 8
#define v9 9
#define v10 10
#define v11 11
#define v12 12
#define v13 13
#define v14 14
#define v15 15
#define v16 16
#define v17 17
#define v18 18
#define v19 19
#define v20 20
#define v21 21
#define v22 22
#define v23 23
#define v24 24
#define v25 25
#define v26 26
#define v27 27
#define v28 28
#define v29 29
#define v30 30
#define v31 31

// RSP COP2 Control Register
#define vco 0   // 16 bit Vector Carry Out
#define vcc 1   // 16 bit Vector Compare Code (8..15 clip, 0..7 compare)
#define vce 2   // 8 bit Vector Compare Extension

#endif
// vim: ft=mips
