#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <time.h>
#include <rcp/vi.h>
#include <vr4300/cache.h>

#include "debug.h"
#include "framebuffer.h"
#include "input.h"
#include "integer.h"
#include "plot.h"
#include "polygon.h"
#include "vector.h"

struct Framebuffer_t g_Screen = {(u16*)0x80100000, FB_WIDTH, FB_HEIGHT
    , FB_WIDTH*FB_HEIGHT*FB_BPP, FB_BPP};

void drawTri(Vec3 tri[3]) {
    drawLine(fixdiv(tri[0].x, tri[0].z), fixdiv(tri[0].y, tri[0].z),
             fixdiv(tri[1].x, tri[1].z), fixdiv(tri[1].y, tri[1].z), 0xFE00, g_Screen.framebuffer);
    drawLine(fixdiv(tri[1].x, tri[1].z), fixdiv(tri[1].y, tri[1].z),
             fixdiv(tri[2].x, tri[2].z), fixdiv(tri[2].y, tri[2].z), 0x0FE0, g_Screen.framebuffer);
    drawLine(fixdiv(tri[2].x, tri[2].z), fixdiv(tri[2].y, tri[2].z),
             fixdiv(tri[0].x, tri[0].z), fixdiv(tri[0].y, tri[0].z), 0x00FE, g_Screen.framebuffer);
}

Vec3 line = {250,250,10};
Vec2 quad[4] = {{190,170},{240,190},{230,210},{200,200}};
Vec3 tri[3] = {{140,140,0x180},{180,140,0x180},{160,180,0x180}};
Vec2 tri2[3] = {{200,170},{240,180},{210,210}};

static vi_state_t vi_state = {
	VI_BPP16 \
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

__attribute__((noreturn)) int main(void)
{
    vi_flush_state(&vi_state);
    /*Joypad_t player1_joy, player2_joy;*/

    /*initJoypad();*/

    while (1) {

        clock_t t_start = get_ticks_us();
        /*updateJoypads();

        readJoypad(0, &player1_joy);
        readJoypad(1, &player2_joy);*/
        line.x += 128;//player1_joy.analog_x;
        line.y += 128;//player2_joy.analog_y;

        tri2[0].x = 350+(isin(line.x+0x4000)>>7);
        tri2[0].y = 150+(isin(line.x+0x2000)>>7);
        tri2[1].x = 200+(isin(line.x+0x8000)>>7);
        tri2[1].y = 200+(isin(line.x+0x4000)>>7);
        tri2[2].x = 350+(isin(line.x+0xa000)>>7);
        tri2[2].y = 300+(isin(line.x+0x6000)>>7);
        fillTriangle(tri2, 0xDA55, g_Screen.framebuffer);

        tri2[0].x = 100;
        tri2[0].y = -50;
        tri2[1].x = 150;
        tri2[1].y = 100;
        tri2[2].x = 50;
        tri2[2].y = 100;
        fillTriangle(tri2, 0xDA55, g_Screen.framebuffer);

        tri2[0].x = 100;
        tri2[0].y = -50;
        tri2[1].x = 138;
        tri2[1].y = 75;
        tri2[2].x = 62;
        tri2[2].y = 75;
        fillTriangle(tri2, 0x0A50, g_Screen.framebuffer);

        tri2[0].x = -50+(isin(line.x+0x4000)>>7);
        tri2[0].y = -50+(isin(line.x+0x2000)>>7);
        tri2[1].x = 50+(isin(line.x+0x8000)>>7);
        tri2[1].y = 50+(isin(line.x+0x4000)>>7);
        tri2[2].x = -50+(isin(line.x+0xa000)>>7);
        tri2[2].y = 50+(isin(line.x+0x6000)>>7);
        fillTriangle(tri2, 0x0f00, g_Screen.framebuffer);

        tri[0].x = 200+(isin(line.x+0x4000)>>7);
        tri[1].y = 120+(isin(line.y+0x2000)>>7);
        tri[1].x = 180+(isin(line.x+0x1000)>>7);
        tri[2].x = 200+(isin(line.x)>>7);
        drawTri(tri);

        for(int i=0x1000;i-=8;) {
            drawLine(100+(isin(i+line.x)>>5)/line.z, 100+(icos(i+line.x)>>5)/line.z, 100, 100, 0xFE00, g_Screen.framebuffer);
        }

        drawCircle(100,100,50,0xF800,g_Screen.framebuffer);

        clock_t t_end = get_ticks_us();
        clock_t dt = t_end - t_start;

        writeback_dcache_all();
        waitScanline(240);
        swapFramebuffer(&g_Screen);
        for(size_t i = 0; i < g_Screen.size/sizeof(*g_Screen.framebuffer); i++) {
            g_Screen.framebuffer[i] = 0;
        }
    }
}

