#include <stdint.h>
#include <rcp/rdp.h>
#include <rcp/vi.h>
#include <vr4300/cache.h>

#include "framebuffer.h"
#include "plot.h"

struct Framebuffer_t g_Screen = {(u16*)KSEG0(Framebuffer), FB_WIDTH, FB_HEIGHT
    , FB_WIDTH*FB_HEIGHT*FB_BPP, FB_BPP};

int main(void)
{
    static vi_state_t vi_state;
    vi_setup_res(VI_RES_320x240, &vi_state);
    vi_state.status |= VI_BPP16;// | GAMMA_EN | GAMMA_DITHER_EN;
    vi_state.origin = Framebuffer;
    vi_flush_state(&vi_state);

    unsigned frame = 0;

    //glClearColor16(0, 0, 0);
    writeback_dcache_all();
    while(1) {
        /*for(unsigned i = 0; i < g_Screen.size/FB_BPP; i++) {*/
            /*g_Screen.framebuffer[i] = 0x404;*/
        /*}*/
        frame & 1
            ? drawMeC()
            : drawMeAsm();
        while (rdp_is_busy());

        waitScanline(240);
        //glClear(GL_COLOR_BUFFER_BIT);
        frame++;
    }
    return 0;
}

