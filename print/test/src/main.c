#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <rcp/vi.h>
#include <rcp/rsp.h>

#include "print.h"

#define RGB15(R, G, B) (((R) & 0x1f)<<11 | ((G) & 0x1f)<<6 | ((B) & 0x1f)<<1)

#define Framebuffer 0x00100000
#define FB_WIDTH 320
#define FB_HEIGHT 240


int main(void) {
    /*
    static struct console_t console = {
        .framebuffer = (uint16_t *)KSEG0(Framebuffer),
        .x = 8,
        .y = 0,
        .width = FB_WIDTH,
        .height = FB_HEIGHT,
        .color = 0xFFFF,
        .bg_color = 0xf0f0,
        .opaque = 1,
        .margin = {
            .top = 8,
            .bottom = 8,
            .left = 8,
            .right = 8
        },
        .line_spacing = 12
    };
    initConsole(&console);
    */

    struct console_t * console = console_init_simple (KSEG0(Framebuffer), FB_WIDTH, FB_HEIGHT);

    console->bg_color = 0x24;
    console_clear();
    puts("this is n64dev");

    console_set_pos(18,55);
    console->margin.left = 18;
    /*puts("Greetings, traveler!\nI am but a simple water filter salesman");*/

    printf("\tHexa:\t");
    console_set_color(RGB15(28,28,28), RGB15(5,5,5));
    printf("0x%x 0x%x\n", 0xfeed, 0xbacc);
    printf("%s=0%xh", "out", 123);
    printf("\n%%bits and bobs %b\n%b", 0xff, ~0x800000);
    printf("\n%d %d %d %d %d\n%d %d", 4, -4, 1337, 21139179, 0x8000000, 0x80000000, 0xffffffff);

    printf ("round %d %d", (int)roundf( 42.6f), (int)round( 42.6));
    printf (" %d %d\n",    (int)roundf(-42.1f), (int)round(-42.1));
    printf ("floor %d %d", (int)floorf( 42.6f), (int)floor( 42.6));
    printf (" %d %d\n",    (int)floorf(-42.6f), (int)floor(-42.6));
    printf ("ceil  %d %d", (int)ceilf ( 42.6f), (int)ceil ( 42.6));
    printf (" %d %d",      (int)ceilf (-42.6f), (int)ceil (-42.6));
    /*printf("hello\nworld\nfoo\nbar\ncar\nparts\ncarts\npaul\nblart\nmall\nsplart\ndart\nmario\nkart");*/

    console_flush();

    vi_state_t vi_state;
    vi_setup_res(VI_RES_320x240, &vi_state);
    vi_state.status |= VI_BPP16;// | GAMMA_EN | GAMMA_DITHER_EN;
    vi_state.origin = Framebuffer;
    vi_flush_state(&vi_state);

    while(1) {

        vi_wait_scanline(240);    // wait for vblank
    }
    return 0;
}

