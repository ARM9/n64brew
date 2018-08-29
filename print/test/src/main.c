#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <rcp/vi.h>
#include <rcp/rsp.h>
#include <vr4300/cache.h>

#include "print.h"
#include "framebuffer.h"

#define RGB15(R, G, B) (((R) & 0x1f)<<11 | ((G) & 0x1f)<<6 | ((B) & 0x1f)<<1)

#define Framebuffer 0x00100000
#define FB_WIDTH 320
#define FB_HEIGHT 240
#define FB_BPP 2

static vi_state_t vi_state;

int main(void) {
    /*static struct console_t console = {*/
        /*.framebuffer = (uint16_t *)KSEG0(Framebuffer),*/
        /*.x = 8,*/
        /*.y = 0,*/
        /*.width = FB_WIDTH,*/
        /*.height = FB_HEIGHT,*/
        /*.color = 0xFFFF,*/
        /*.bg_color = 0xf0f0,*/
        /*.opaque = 1,*/
        /*.margin = {*/
            /*.top = 8,*/
            /*.bottom = 8,*/
            /*.left = 8,*/
            /*.right = 8*/
        /*},*/
        /*.line_spacing = 12*/
    /*};*/
    /*initConsole(&console);*/

    struct console_t * console = initConsoleSimple (KSEG0(Framebuffer), FB_WIDTH, FB_HEIGHT);

    console->bg_color = 0x24;
    consoleClear();
    printf("this is n64dev");

    /*writeback_dcache_all();*/

    consoleSetPos(18,55);
    console->margin.left = 18;
    /*puts("Greetings, traveler!\nI am but a simple water filter salesman");*/
    /*consoleClear();*/

    printf("\tHexa:\t");
    consoleSetColor(RGB15(31,0,0), RGB15(9,9,9));
    printf("0x%x 0x%x\n", 0xfeed, 0xbacc);
    printf("check this %s=0%xh", "out", 123);
    printf("\n%%bits and bobs %b\n%b", 0xff, ~0x800000);
    printf("\n%d %d %d %d %d\n%d %d", 4, -4, 1337, 21139179, 0x8000000, 0x80000000, 0xffffffff);

    /*printf("hello\nworld\nfoo\nbar\ncar\nparts\ncarts\npaul\nblart\nmall\nsplart\ndart\nmario\nkart");*/

    writeback_dcache_all();

    vi_setup_res(VI_RES_320x240, &vi_state);
    vi_state.status |= VI_BPP16;// | GAMMA_EN | GAMMA_DITHER_EN;
    vi_state.origin = Framebuffer;
    vi_flush_state(&vi_state);

    while(1) {

        waitScanline(240);    // wait for vblank
    }
    return 0;
}

