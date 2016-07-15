#include <rcp/vi.h>

#include "framebuffer.h"
#include "plot.h"
#include "integer.h"

#define RGB15(r, g, b) ((r)>>3<<11|(g)>>3<<6|(b)>>3<<1)

struct Framebuffer_t g_Screen = {(u16*)0xA0100000, FB_WIDTH, FB_HEIGHT
    , FB_WIDTH*FB_HEIGHT*FB_BPP, FB_BPP};

static vi_state_t vi_state = {
	0x0000324E, // status
	0x00100000, // origin
	0x00000140, // width
	0x00000002, // intr 0x200
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

int main(void)
{
    vi_flush_state(&vi_state);

    unsigned frame = 0;

    //glClearColor16(0, 0, 0);
    while(1) {
        frame & 1
            ? drawMeC()
            : drawMeAsm();
        ++frame;

        waitScanline(240);
        swapFramebuffer(&g_Screen);
        //glClear(GL_COLOR_BUFFER_BIT);
        for(unsigned i = 0; i < g_Screen.size/FB_BPP; i++) {
            g_Screen.framebuffer[i] = 0;
        }
    }
    return 0;
}

