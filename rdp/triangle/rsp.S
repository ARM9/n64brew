        #include "rspdefs.S"

	.align 3
	.global test_tile
test_tile:
	.incbin "chenghost.bin"
	.global rsp_beg
	.global rsp_end
rsp_beg:
	lui $a0, 0xA000
	addiu $a0, $a0, 0x20

	/* set stuff up */
	la $t0, (0x00<<24)
	sw $t0, 0($a0)
	la $t1, 0
	sw $t1, 4($a0)

	la $t0, (0x2F<<24) | (3<<20) | (15<<4) | 15;
	sw $t0, 8($a0)
	la $t1, (0x0000<<16) | 0
	sw $t1, 12($a0)

	la $t0, (0x3C<<24) | 0x00FFFFFF
	sw $t0, 16($a0)
	la $t1, 0xFFFDFF3F
	sw $t1, 20($a0)

	la $t0, (0x37<<24)
	sw $t0, 24($a0)
	la $t1, 0xFF0000FF
	sw $t1, 28($a0)
	
	/* draw our triangle */
	/* s0,s1,s2 == X */
	/* s3,s4,s5 == Y */
	lh $s0, 0x10($zero)
	lh $s1, 0x14($zero)
	lh $s2, 0x18($zero)

	lh $s3, 0x12($zero)
	lh $s4, 0x16($zero)
	lh $s5, 0x1A($zero)

	/* set X positions */
	sll $t0, $s0, 16
	sll $t1, $s1, 16
	sw $t1, 40($a0)
	sw $t0, 48($a0)
	sw $t0, 56($a0)

	/* do some setup for gradients */
	VXOR(0, 0, 0, 0)
	VXOR(1, 1, 1, 0)
	VXOR(2, 2, 2, 0)
	VXOR(3, 3, 3, 0)

	/* gradient calculations */
	/* minor: downwards s6,s7 */
	/* major: downwards s8 */
	subu $s6, $s4, $s3
	subu $s7, $s5, $s4
	subu $s8, $s5, $s3
	subu $t0, $s1, $s0
	subu $t1, $s2, $s1
	subu $t2, $s2, $s0

	/* V1: Y gradients */
	MTC2(R_S6, 1, 0)
	MTC2(R_S7, 1, 2)
	MTC2(R_S8, 1, 4)

	/* V2: X gradients */
	MTC2(R_T0, 2, 0)
	MTC2(R_T1, 2, 2)
	MTC2(R_T2, 2, 4)

	VXOR(5, 5, 5, 0)
	VXOR(4, 4, 4, 0)

	/* V3: reciprocal of Y gradients */
	VXOR(0, 0, 0, 0)
	/*
	VXOR(6, 6, 6, 0)
	VRCPH(6, 0, 0, 0)
	VRCPL(3, 0, 1, 0)
	VRCPH(6, 0, 0, 0)
	VRCPL(3, 1, 1, 2)
	VRCPH(6, 1, 0, 0)
	VRCPL(3, 2, 1, 4)
	VRCPH(6, 2, 0, 0)
	*/
	VRCP(3, 0, 1, 0)
	VRCP(3, 1, 1, 2)
	VRCP(3, 2, 1, 4)

	/* V4/5: DX*(1/DY) hi/lo */
	VXOR(0, 0, 0, 0)
	VMUDN(5, 2, 3, 0)
	VMADM(4, 0, 0, 0)
	//VMUDM(4, 3, 2, 0)
	//VOR(5, 3, 3, 0)
	//VOR(4, 6, 6, 0)

	/* double it */
	VADDC(5, 5, 5, 0)
	VADD (4, 4, 4, 0)

	/* store it all */
	SSV(4, 2, 44, R_A0)
	SSV(5, 2, 46, R_A0)
	SSV(4, 4, 52, R_A0)
	SSV(5, 4, 54, R_A0)
	SSV(4, 0, 60, R_A0)
	SSV(5, 0, 62, R_A0)

	/* set Y values + major side */
	la $t0, (0x08<<24) | (1<<23)
	sll $t2, $s5, 2
	andi $t2, $t2, 0x3FFF
	or $t0, $t0, $t2
	sw $t0, 32($a0)

	sll $t3, $s4, 18
	sll $t4, $s3, 2
	andi $t4, $t4, 0x3FFF
	or $t1, $t3, $t4
	sw $t1, 36($a0)

	la $t0, 64
	la $t1, 0x0002
	mtc0 $t1, $11
	addu $a1, $a0, $t0

	1:
		mfc0 $t2, $11
		nop
		andi $t2, $t2, (3<<9)
		bnez $t2, 1b
		nop

	mtc0 $a0, $8
	mtc0 $a1, $9
	break
	nop
rsp_end:
// vim:ft=mips
