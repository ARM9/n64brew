#include <string.h>
#include <rcp/vi.h>
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

    initConsoleSimple(KSEG1(Framebuffer), FB_WIDTH, FB_HEIGHT);

    consoleClear();

    consoleSetPos(80,64);
    consoleSetMargins(8,8,64,8);
    char msg[] = "Greetings, traveler!\n";
    for (size_t i = 0; i < strlen(msg); i++) {
        consoleSetFgColor(RGB15(29-i,0,i+7));
        putchar(msg[i]);
    }
    consoleSetFgColor(RGB15(31,31,31));
    puts("This is a simple console.");
    puts("64 in 3 different bases:");
    consoleSetFgColor(RGB15(0,19,28));
    printf("\n\t%d\n\t0x%x\n\t0b%b", 64, 64, 64);

    writeback_dcache_all();

    // turn on screen
    vi_setup_res(VI_RES_320x240, &vi_state);
    vi_state.status |= VI_BPP16;// | GAMMA_EN | GAMMA_DITHER_EN;
    vi_state.origin = Framebuffer;
    vi_flush_state(&vi_state);

    while(1) {
    }
    return 0;
}

