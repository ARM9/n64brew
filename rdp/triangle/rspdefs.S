
#define FMT_LV(op, vt, elem, offset, base) \
	.word 0xC8000000 | (((base) & 31)<<21) | (((vt) & 31)<<16) | (((op) & 31)<<11) | (((elem) & 15)<<7) | ((offset) & 127)

#define FMT_SV(op, vt, elem, offset, base) \
	.word 0xE8000000 | (((base) & 31)<<21) | (((vt) & 31)<<16) | (((op) & 31)<<11) | (((elem) & 15)<<7) | ((offset) & 127)

#define FMT_COP2_3B(op, vd, vs, vt, e) \
	.word 0x4A000000 | (((e) & 15)<<21) | (((vt) & 31)<<16) | (((vs) & 31)<<11) | (((vd) & 31)<<6) | ((op) & 63)

#define FMT_COP2_3D(op, vd, de, vt, e) \
	.word 0x4A000000 | (((e) & 15)<<21) | (((vt) & 31)<<16) | (((de) & 31)<<11) | (((vd) & 31)<<6) | ((op) & 63)

#define MFC2(rt, rd, elem) \
	.word 0x48000000 | (((rt) & 31)<<16) | (((rd) & 31)<<11) | (((elem) & 15)<<7)

#define MTC2(rt, rd, elem) \
	.word 0x48800000 | (((rt) & 31)<<16) | (((rd) & 31)<<11) | (((elem) & 15)<<7)

#define LHV(vt, offset, base) FMT_LV( 8, vt, 0, offset, base)
#define LPV(vt, offset, base) FMT_LV( 6, vt, 0, offset, base)
#define LQV(vt, offset, base) FMT_LV( 4, vt, 0, offset, base)
#define LRV(vt, offset, base) FMT_LV( 5, vt, 0, offset, base)
#define LUV(vt, offset, base) FMT_LV( 7, vt, 0, offset, base)

#define LBV(vt, elem, offset, base) FMT_LV( 0, vt, elem, offset, base)
#define LDV(vt, elem, offset, base) FMT_LV( 3, vt, elem, (offset)>>3, base)
#define LFV(vt, elem, offset, base) FMT_LV( 9, vt, elem, offset, base)
#define LLV(vt, elem, offset, base) FMT_LV( 2, vt, elem, (offset)>>2, base)
#define LSV(vt, elem, offset, base) FMT_LV( 1, vt, elem, (offset)>>1, base)
#define LTV(vt, elem, offset, base) FMT_LV(11, vt, elem, offset, base)
//define LWV(vt, elem, offset, base) FMT_LV(10, vt, elem, offset, base)

#define SHV(vt, offset, base) FMT_SV( 8, vt, 0, offset, base)
#define SPV(vt, offset, base) FMT_SV( 6, vt, 0, offset, base)
#define SQV(vt, offset, base) FMT_SV( 4, vt, 0, offset, base)
#define SRV(vt, offset, base) FMT_SV( 5, vt, 0, offset, base)
#define SUV(vt, offset, base) FMT_SV( 7, vt, 0, offset, base)

#define SBV(vt, elem, offset, base) FMT_SV( 0, vt, elem, offset, base)
#define SDV(vt, elem, offset, base) FMT_SV( 3, vt, elem, (offset)>>3, base)
#define SFV(vt, elem, offset, base) FMT_SV( 9, vt, elem, offset, base)
#define SLV(vt, elem, offset, base) FMT_SV( 2, vt, elem, (offset)>>2, base)
#define SSV(vt, elem, offset, base) FMT_SV( 1, vt, elem, (offset)>>1, base)
#define STV(vt, elem, offset, base) FMT_SV(11, vt, elem, offset, base)
#define SWV(vt, elem, offset, base) FMT_SV(10, vt, elem, offset, base)

#define VABS(vd, vs, vt, e) FMT_COP2_3B(19, vd, vs, vt, e)
#define VADD(vd, vs, vt, e) FMT_COP2_3B(16, vd, vs, vt, e)
#define VADDC(vd, vs, vt, e) FMT_COP2_3B(20, vd, vs, vt, e)
#define VAND(vd, vs, vt, e) FMT_COP2_3B(40, vd, vs, vt, e)
#define VCH(vd, vs, vt, e) FMT_COP2_3B(37, vd, vs, vt, e)
#define VCL(vd, vs, vt, e) FMT_COP2_3B(36, vd, vs, vt, e)
#define VCR(vd, vs, vt, e) FMT_COP2_3B(38, vd, vs, vt, e)
#define VEQ(vd, vs, vt, e) FMT_COP2_3B(33, vd, vs, vt, e)
#define VGE(vd, vs, vt, e) FMT_COP2_3B(35, vd, vs, vt, e)
#define VLT(vd, vs, vt, e) FMT_COP2_3B(32, vd, vs, vt, e)
#define VMACF(vd, vs, vt, e) FMT_COP2_3B(8, vd, vs, vt, e)
#define VMACQ(vd, vs, vt, e) FMT_COP2_3B(11, vd, vs, vt, e)
#define VMACU(vd, vs, vt, e) FMT_COP2_3B(9, vd, vs, vt, e)
#define VMADH(vd, vs, vt, e) FMT_COP2_3B(15, vd, vs, vt, e)
#define VMADL(vd, vs, vt, e) FMT_COP2_3B(12, vd, vs, vt, e)
#define VMADM(vd, vs, vt, e) FMT_COP2_3B(13, vd, vs, vt, e)
#define VMADN(vd, vs, vt, e) FMT_COP2_3B(14, vd, vs, vt, e)
#define VMOV(vd, de, vt, e) FMT_COP2_3D(51, vd, de, vt, e)
#define VMRG(vd, vs, vt, e) FMT_COP2_3B(39, vd, vs, vt, e)
#define VMUDH(vd, vs, vt, e) FMT_COP2_3B(7, vd, vs, vt, e)
#define VMUDL(vd, vs, vt, e) FMT_COP2_3B(4, vd, vs, vt, e)
#define VMUDM(vd, vs, vt, e) FMT_COP2_3B(5, vd, vs, vt, e)
#define VMUDN(vd, vs, vt, e) FMT_COP2_3B(6, vd, vs, vt, e)
#define VMULF(vd, vs, vt, e) FMT_COP2_3B(0, vd, vs, vt, e)
#define VMULQ(vd, vs, vt, e) FMT_COP2_3B(3, vd, vs, vt, e)
#define VMULU(vd, vs, vt, e) FMT_COP2_3B(1, vd, vs, vt, e)
#define VNAND(vd, vs, vt, e) FMT_COP2_3B(41, vd, vs, vt, e)
#define VNE(vd, vs, vt, e) FMT_COP2_3B(34, vd, vs, vt, e)
#define VNOP(vd, vs, vt, e) FMT_COP2_3B(56, vd, vs, vt, e)
#define VNOR(vd, vs, vt, e) FMT_COP2_3B(43, vd, vs, vt, e)
#define VNXOR(vd, vs, vt, e) FMT_COP2_3B(45, vd, vs, vt, e)
#define VOR(vd, vs, vt, e) FMT_COP2_3B(42, vd, vs, vt, e)
#define VRCP(vd, de, vt, e) FMT_COP2_3D(48, vd, de, vt, e)
#define VRCPH(vd, de, vt, e) FMT_COP2_3D(50, vd, de, vt, e)
#define VRCPL(vd, de, vt, e) FMT_COP2_3D(49, vd, de, vt, e)
#define VRNDN(vd, vs, vt, e) FMT_COP2_3B(10, vd, vs, vt, e)
#define VRNDP(vd, vs, vt, e) FMT_COP2_3B(2, vd, vs, vt, e)
#define VRSQ(vd, de, vt, e) FMT_COP2_3D(52, vd, de, vt, e)
#define VRSQH(vd, de, vt, e) FMT_COP2_3D(54, vd, de, vt, e)
#define VRSQL(vd, de, vt, e) FMT_COP2_3D(53, vd, de, vt, e)
#define VSAR(vd, vs, vt, e) FMT_COP2_3B(29, vd, vs, vt, e)
#define VSUB(vd, vs, vt, e) FMT_COP2_3B(17, vd, vs, vt, e)
#define VSUBC(vd, vs, vt, e) FMT_COP2_3B(21, vd, vs, vt, e)
#define VXOR(vd, vs, vt, e) FMT_COP2_3B(44, vd, vs, vt, e)

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
