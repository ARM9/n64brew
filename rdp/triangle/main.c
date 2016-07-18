#include <string.h>
#include <stdint.h>
#include <vr4300/cache.h>

const uint8_t test_tile[16*2+64*32];
const uint8_t rsp_beg[1024*4], rsp_end[1];
volatile uint32_t rdp_list[1024] __attribute__((aligned(8)));

int ridx_fence = 2;
int ridx = 2;

/*
static int32_t calc_dde(int32_t v1, int32_t v3, int32_t y13)
{
	return (v3-v1)/y13;
}
*/

void set_cmb1(
	int cmb_RA, int cmb_RB, int cmb_RC, int cmb_RD,
	int cmb_LA, int cmb_LB, int cmb_LC, int cmb_LD)
{
	cmb_RA &= 15;
	cmb_RB &= 15;
	cmb_RC &= 31;
	cmb_RD &= 7;
	cmb_LA &= 7;
	cmb_LB &= 7;
	cmb_LC &= 7;
	cmb_LD &= 7;

	uint32_t cmb_0 = (0x3C<<24);
	uint32_t cmb_1 = 0;
	cmb_0 |= (cmb_RA<<20) | (cmb_RA<< 5);
	cmb_0 |= (cmb_LA<<12) | (cmb_LC<< 9);
	cmb_0 |= (cmb_RC<<15) | (cmb_RC<< 0);
	cmb_1 |= (cmb_LA<<21) | (cmb_LC<<18);
	cmb_1 |= (cmb_RB<<28) | (cmb_RB<<24);
	cmb_1 |= (cmb_RD<<15) | (cmb_RD<< 6);
	cmb_1 |= (cmb_LB<<12) | (cmb_LB<< 3);
	cmb_1 |= (cmb_LD<< 9) | (cmb_LD<< 0);

	rdp_list[ridx++] = cmb_0;
	rdp_list[ridx++] = cmb_1;

}

void main(void)
{
	//int x, y;

	// set up a screen
	*(volatile uint32_t *)0xA4400000 = 0x00000003;
	*(volatile uint32_t *)0xA4400004 = 0xA0100000;
	*(volatile uint32_t *)0xA4400008 = 320;
	*(volatile uint32_t *)0xA440000C = 0x200;
	*(volatile uint32_t *)0xA4400010 = 0;
	*(volatile uint32_t *)0xA4400014 = 0x03E52239;
	*(volatile uint32_t *)0xA4400018 = 525;
	*(volatile uint32_t *)0xA440001C = 0x00000C15;
	*(volatile uint32_t *)0xA4400020 = 0x0C150C15;
	*(volatile uint32_t *)0xA4400024 = 0x006C02EC;
	*(volatile uint32_t *)0xA4400028 = 0x002501FF;
	*(volatile uint32_t *)0xA440002C = 0x000E0204;
	*(volatile uint32_t *)0xA4400030 = 0x200;
	*(volatile uint32_t *)0xA4400034 = 0x400;

	// fill screen
	/*
	for(y = 0; y < 240; y++) {
	for(x = 0; x < 320; x++) {
		((volatile uint32_t *)0xA0100000)[320*y+x]
			= 0x000000FF
			| ((x*255/320)<<8)
			| ((y*255/240)<<16)
			;
	}
	}
	*/

	// bang out RDP commands
	*(volatile uint32_t *)0xA410000C = 0x01;

	rdp_list[ridx++] = (0x2D<<24) | (0<<12) | 0;
	rdp_list[ridx++] = ((320<<2)<<12) | (240<<2);

	int cycle_type = 0;
	rdp_list[ridx++] = (0x2F<<24) | (0<<23) | (cycle_type<<20) | (15<<4) | 15;
	rdp_list[ridx++] = (0x0000<<16) | 0;
	rdp_list[ridx++] = (0x3F<<24) | (0<<21) | (3<<19) | (320-1);
	rdp_list[ridx++] = 0x00100000;

	// set TLUT + tile data
	rdp_list[ridx++] = (0x26<<24);
	rdp_list[ridx++] = 0;

	rdp_list[ridx++] = (0x3D<<24) | (0<<21) | (2<<19) | (16-1);
	rdp_list[ridx++] = (uint32_t)&test_tile[2*16];
	rdp_list[ridx++] = (0x35<<24) | (0<<21) | (2<<19) | (4<<9) | ((0x000)>>3);
	rdp_list[ridx++] = (0<<24) | (0<<20) | (0x05B<<10) | (0x05B);
	rdp_list[ridx++] = (0x34<<24) | ((0<<2)<<12) | (0<<2);
	rdp_list[ridx++] = (0<<24) | ((31<<2)<<12) | (63<<2);

	rdp_list[ridx++] = (0x28<<24);
	rdp_list[ridx++] = 0;

	rdp_list[ridx++] = (0x3D<<24) | (0<<21) | (2<<19) | (1-1);
	rdp_list[ridx++] = (uint32_t)&test_tile[0];
	rdp_list[ridx++] = (0x35<<24) | (0<<21) | (0<<19) | (0<<9) | (0x800>>3);
	rdp_list[ridx++] = (0 << 24) | (0<<20) | (0x05B<<10) | (0x05B);
	rdp_list[ridx++] = (0x30<<24) | (((0)<<2)<<12);
	rdp_list[ridx++] = (0<<24) | (((16-1)<<2)<<12);

	rdp_list[ridx++] = (0x28<<24);
	rdp_list[ridx++] = 0;

	rdp_list[ridx++] = (0x35<<24) | (2<<21) | (0<<19) | (4<<9) | ((0x000)>>3);
	rdp_list[ridx++] = (0<<24) | (0<<20) | (0x06B<<10) | (0x06B);

	rdp_list[ridx++] = (0x28<<24);
	rdp_list[ridx++] = 0;

	rdp_list[ridx++] = (0x3A<<24);
	rdp_list[ridx++] = 0x200000FF;
	//rdp_list[ridx++] = 0xFFFFFFFF;
	//rdp_list[ridx++] = 0x202020FF;

	set_cmb1(7, 8, 3, 4, 7, 7, 7, 7);

	// clear w/ gradient
#if 1
	rdp_list[ridx++] = (0x0C<<24) | (1<<23) | (0<<19) | (0<<16) | ((240<<2)<<0);
	rdp_list[ridx++] = ((240<<2)<<16) | ((0<<2)<<0);
	rdp_list[ridx++] = 320<<16;
	rdp_list[ridx++] = 0; // XL (lower)
	rdp_list[ridx++] = 0<<16;
	rdp_list[ridx++] = 0; // XH (major)
	rdp_list[ridx++] = 320<<16;
	rdp_list[ridx++] = 0; // XM (upper)

	rdp_list[ridx++] = 0x00000000; rdp_list[ridx++] = 0x00000000;
	rdp_list[ridx++] = 0x00000000; rdp_list[ridx++] = 0x00000000;
	rdp_list[ridx++] = 0x80008000; rdp_list[ridx++] = 0x80008000;
	rdp_list[ridx++] = 0x00000000; rdp_list[ridx++] = 0xCC000000;

	rdp_list[ridx++] = 0x00000001; rdp_list[ridx++] = 0x00000000;
	rdp_list[ridx++] = 0x00000001; rdp_list[ridx++] = 0x00000000;
	rdp_list[ridx++] = 0x00001000; rdp_list[ridx++] = 0x00000000;
	rdp_list[ridx++] = 0x00001000; rdp_list[ridx++] = 0x00000000;
#endif

	//rdp_list[ridx++] = (0x37<<24); rdp_list[ridx++] = 0x0000FFFF;
	rdp_list[ridx++] = (0x29<<24); rdp_list[ridx++] = 0;

	/*
	for(;;) {
		uint32_t v = *(volatile uint32_t *)0xA410000C;
		if((v & (3<<9)) == 0) {
			break;
		}
	}
	*(volatile const void **)0xA4100000 = &rdp_list[ridx_fence];
	*(volatile const void **)0xA4100004 = &rdp_list[ridx];
	ridx_fence = ridx;
	*/

	// Points on triangle
	int32_t x1 = 120, y1 = 50;
	int32_t x2 = 240, y2 = 130;
	int32_t x3 = 100, y3 = 210;

	// Colours + texcoords
	int32_t cr1 = 0x00000000;
	int32_t cg1 = 0x00000000;
	int32_t cb1 = 0x00FF0000;
	int32_t ca1 = 0x00000000;
	int32_t ts1 = 96<<16;
	int32_t tt1 = 0<<16;
	int32_t tw1 = 0x7FFFFFFF;

	int32_t cr2 = 0x00000000;
	int32_t cg2 = 0x00FF0000;
	int32_t cb2 = 0x00000000;
	int32_t ca2 = 0x00000000;
	int32_t ts2 = 160<<16;
	int32_t tt2 = 128<<16;
	int32_t tw2 = 0x7FFFFFFF;

	int32_t cr3 = 0x00FF0000;
	int32_t cg3 = 0x00000000;
	int32_t cb3 = 0x00000000;
	int32_t ca3 = 0x00000000;
	int32_t ts3 = 32<<16;
	int32_t tt3 = 128<<16;
	int32_t tw3 = 0x7FFFFFFF;

	// X,Y diffs
	int32_t x12 = x2-x1;
	int32_t x23 = x3-x2;
	int32_t x13 = x3-x1;
	int32_t y12 = y2-y1;
	int32_t y23 = y3-y2;
	int32_t y13 = y3-y1;

	// X gradients
	int32_t xgrad12 = (x12<<16)/y12;
	int32_t xgrad13 = (x13<<16)/y13;
	int32_t xgrad23 = (x23<<16)/y23;

	// X on major at YM + diff
	//int32_t xm = x1+((y12*xgrad13)>>16);
	int32_t xm = x1+y12*x13/y13;
	int32_t xm2 = x2-xm;

	// Colour + texcoord gradients

	// Calc the major edge
	int32_t crde = (cr3-cr1)/y13;
	int32_t cgde = (cg3-cg1)/y13;
	int32_t cbde = (cb3-cb1)/y13;
	int32_t cade = (ca3-ca1)/y13;
	int32_t tsde = (ts3-ts1)/y13;
	int32_t ttde = (tt3-tt1)/y13;
	int32_t twde = (tw3-tw1)/y13;

	// Calc colours + texcoords at major split
	int32_t crm = cr1+crde*y12;
	int32_t cgm = cg1+cgde*y12;
	int32_t cbm = cb1+cbde*y12;
	int32_t cam = ca1+cade*y12;
	int32_t tsm = ts1+tsde*y12;
	int32_t ttm = tt1+ttde*y12;
	int32_t twm = tw1+twde*y12;

	// Calc X
	int32_t crdx = (cr2-crm)/xm2;
	int32_t cgdx = (cg2-cgm)/xm2;
	int32_t cbdx = (cb2-cbm)/xm2;
	int32_t cadx = (ca2-cam)/xm2;
	int32_t tsdx = (ts2-tsm)/xm2;
	int32_t ttdx = (tt2-ttm)/xm2;
	int32_t twdx = (tw2-twm)/xm2;

	// Calc Y because for some reason we have to
	// TODO: verify
	int32_t crdy = crde + crdx*x13/y13;
	int32_t cgdy = cgde + cgdx*x13/y13;
	int32_t cbdy = cbde + cbdx*x13/y13;
	int32_t cady = cade + cadx*x13/y13;
	int32_t tsdy = tsde + tsdx*x13/y13;
	int32_t ttdy = ttde + ttdx*x13/y13;
	int32_t twdy = twde + twdx*x13/y13;

	//rdp_list[ridx++] = (0x29<<24); rdp_list[ridx++] = 0;
	rdp_list[ridx++] = (0x00<<24); rdp_list[ridx++] = 0;

	// Make triangle
	rdp_list[ridx++] = (0x29<<24);
	rdp_list[ridx++] = 0;
	//set_cmb1(1, 8, 4, 3, 7, 7, 7, 7);
	//set_cmb1(7, 8, 16, 1, 7, 7, 7, 7);
	set_cmb1(4, 8, 1, 7, 7, 7, 7, 7);
	//set_cmb1(1, 15, 1, 7, 1, 7, 0, 7);

	rdp_list[ridx++] = (0x2F<<24) | (0<<23) | (cycle_type<<20) | (0<<19) | (2<<14) | (0<<13) | (3<<10) | (15<<4) | 15;
	rdp_list[ridx++] = (0x0000<<16) | (1<<14) | (1<<6) | 0;
	rdp_list[ridx++] = (0x0E<<24) | (0<<19) | (0<<16) | ((y3<<2)<<0);
	if(xm < x2) {
	//if(xgrad13 < xgrad12) {
		rdp_list[ridx-1] |= 1<<23; // left major
	}
	rdp_list[ridx++] = ((y2<<2)<<16) | ((y1<<2)<<0);

	rdp_list[ridx++] = x2<<16;
	rdp_list[ridx++] = xgrad23; // XL (lower)
	rdp_list[ridx++] = x1<<16;
	rdp_list[ridx++] = xgrad13; // XH (major)
	rdp_list[ridx++] = x1<<16;
	rdp_list[ridx++] = xgrad12; // XM (upper)

	// Shade coefficients
	rdp_list[ridx++] = (cr1&0xFFFF0000)|(((uint32_t)cg1)>>16);
	rdp_list[ridx++] = (cb1&0xFFFF0000)|(((uint32_t)ca1)>>16);
	rdp_list[ridx++] = (crdx&0xFFFF0000)|(((uint32_t)cgdx)>>16);
	rdp_list[ridx++] = (cbdx&0xFFFF0000)|(((uint32_t)cadx)>>16);
	rdp_list[ridx++] = (cr1<<16)|(cg1&0x0000FFFF);
	rdp_list[ridx++] = (cb1<<16)|(ca1&0x0000FFFF);
	rdp_list[ridx++] = (crdx<<16)|(cgdx&0x0000FFFF);
	rdp_list[ridx++] = (cbdx<<16)|(cadx&0x0000FFFF);

	rdp_list[ridx++] = (crde&0xFFFF0000)|(((uint32_t)cgde)>>16);
	rdp_list[ridx++] = (cbde&0xFFFF0000)|(((uint32_t)cade)>>16);
	rdp_list[ridx++] = (crdy&0xFFFF0000)|(((uint32_t)cgdy)>>16);
	rdp_list[ridx++] = (cbdy&0xFFFF0000)|(((uint32_t)cady)>>16);
	rdp_list[ridx++] = (crde<<16)|(cgde&0x0000FFFF);
	rdp_list[ridx++] = (cbde<<16)|(cade&0x0000FFFF);
	rdp_list[ridx++] = (crdy<<16)|(cgdy&0x0000FFFF);
	rdp_list[ridx++] = (cbdy<<16)|(cady&0x0000FFFF);

	// Tex coefficients
	rdp_list[ridx++] = (ts1 &0xFFFF0000)|(((uint32_t)tt1 )>>16);
	rdp_list[ridx++] = (tw1 &0xFFFF0000);
	rdp_list[ridx++] = (tsdx&0xFFFF0000)|(((uint32_t)ttdx)>>16);
	rdp_list[ridx++] = (twdx&0xFFFF0000);
	rdp_list[ridx++] = (ts1 <<16)|(tt1 &0x0000FFFF);
	rdp_list[ridx++] = (tw1 <<16);
	rdp_list[ridx++] = (tsdx<<16)|(ttdx&0x0000FFFF);
	rdp_list[ridx++] = (twdx<<16);

	rdp_list[ridx++] = (tsde&0xFFFF0000)|(((uint32_t)ttde)>>16);
	rdp_list[ridx++] = (twde&0xFFFF0000);
	rdp_list[ridx++] = (tsdy&0xFFFF0000)|(((uint32_t)ttdy)>>16);
	rdp_list[ridx++] = (twdy&0xFFFF0000);
	rdp_list[ridx++] = (tsde<<16)|(ttde&0x0000FFFF);
	rdp_list[ridx++] = (twde<<16);
	rdp_list[ridx++] = (tsdy<<16)|(ttdy&0x0000FFFF);
	rdp_list[ridx++] = (twdy<<16);

	rdp_list[ridx++] = (0x29<<24);
	rdp_list[ridx++] = 0;

        writeback_dcache_all();

	for(;;) {
		uint32_t v = *(volatile uint32_t *)0xA410000C;
		uint32_t l = *(volatile uint32_t *)0xA4400010;
		if((v & (3<<9)) == 0 && l >= 0x200) {
			break;
		}
	}


	*(volatile uint32_t *)0xA4100000 = (uint32_t)&rdp_list[ridx_fence];
	*(volatile uint32_t *)0xA4100004 = (uint32_t)&rdp_list[ridx];

	*(volatile uint32_t *)0xA4040010 = 0x00000002; // stop RSP

	for(;;) {
		uint32_t v = *(volatile uint32_t *)0xA410000C;
		if((v & 0x07F0) == 0) {
			break;
		}
	}
	ridx_fence = ridx;

	// RSP test
	//memcpy((void *)0xA4001000, rsp_beg, rsp_end-rsp_beg);
	*(volatile uint32_t *)0xA4080000 = 0x00000000;
	memcpy((void *)0xA4001000, rsp_beg, 1024*4);
	*(volatile uint32_t *)0xA4000010 = (120<<16)|50;
	*(volatile uint32_t *)0xA4000014 = (240<<16)|130;
	*(volatile uint32_t *)0xA4000018 = (100<<16)|210;
	//*(volatile uint32_t *)0xA4040010 = 0x00000001;

	for(;;) {}
}
