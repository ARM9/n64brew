#include <string.h>
#include <rcp/vi.h>
#include "print.h"

#define RGB15(R, G, B) (((R) & 0x1f)<<11 | ((G) & 0x1f)<<6 | ((B) & 0x1f)<<1)

#define Framebuffer 0x00100000
#define FB_WIDTH 320
#define FB_HEIGHT 240

static vi_state_t vi_state;

int main(void) {

    console_init_simple(KSEG0(Framebuffer), FB_WIDTH, FB_HEIGHT);

    console_clear();

    // write some wild stuff
    console_set_pos(80,64);
    console_set_margins(8,8,64,8);
    char msg[] = "Greetings, traveler!\n";
    for (size_t i = 0; i < strlen(msg); i++) {
        console_set_fg_color(RGB15(29-i,0,i+7));
        putchar(msg[i]);
    }
    console_set_fg_color(RGB15(31,31,31));
    puts("This is a simple console.");
    puts("64 in 3 different bases:");
    console_set_fg_color(RGB15(0,19,28));
    printf("\n\t%d\n\t0x%x\n\t0b%b", 64, 64, 64);

    console_flush();

    // turn on screen
    vi_setup_res(VI_RES_320x240, &vi_state);
    vi_state.status |= VI_BPP16;
    vi_state.origin = Framebuffer;
    vi_flush_state(&vi_state);

    while(1) {
        vi_wait_scanline(FB_HEIGHT);
    }
    return 0;
}

