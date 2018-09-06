#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <rcp/ai.h>
#include <rcp/vi.h>
#include <vr4300/cache.h>

#include "framebuffer.h"

static vi_state_t vi_state = {
	VI_BPP16
        | GAMMA_EN|GAMMA_DITHER_EN|INTERLACE|AA_MODE_2|PIXEL_ADV_3, // status
	0x00100000, // origin
	0x00000140, // width
	0x00000200, // intr
	0x00000000, // current
	0x03E52239, // burst
	0x0000020D, // v_sync
	0x00000C15, // h_sync
	0x0C150C15, // leap
	0x006C02EC, // h_start
	0x002501FF, // v_start
	0x000E0204, // v_burst
	0x00000200, // x_scale
	0x00000400, // y_scale
};

int isin(int x) {
    const int qN = 13, qA = 12, qP = 15, qR = 2*qN-qP, qS = qN+qP+1-qA;
    x = x << (30 - qN);
    if ((x^(x<<1)) < 0)
        x = (1 << 31) - x;
    x = x >> (30 - qN);
    return x * ((3 << qP) - (x * x >> qR)) >> qS;
}

char __attribute__((aligned(8))) audio[1024] = {};//{0,0,30,30,40,40,20,20,0,0,-20,-20,-50,-50,-60,-60};

int main(void) {
    vi_flush_state(&vi_state);

    for(int i = 3; i < 1023; i+=2) {
        //audio[i] = audio[i-1] = (i % 64 < 32) ? 64 : -64;
        audio[i] = audio[i-1] = sinf(i/180.f*3.1415f)*10;
    }
    
    //const unsigned VI_NTSC_CLOCK = 48681812;

    while (1) {
        writeback_dcache_all();
        *AI_DRAM_ADDR = (unsigned)audio;
        *AI_LEN = 1024;
        *AI_CONTROL = 1; // enable DMA
        *AI_DACRATE = (VI_NTSC_CLOCK/(44100/4))-1;
        *AI_BITRATE = 7; // rate-1

        //while((*AI_STATUS & (1<<0))) {
        //}

        //for(i = 0; i < 100000; i++)
            //asm volatile("":::"memory");
        /*uint32_t scanline = getScanline();
        while(scanline<235){
            scanline = getScanline();
        }*/

        waitScanline(240);    // wait for vblank
    }
    return 0;
}

