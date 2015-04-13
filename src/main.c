#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "libn64.h"
#include "dma.h"
#include "input.h"
#include "numbers.h"
#include "plot.h"
#include "polygon.h"
#include "vector.h"
#include "vi.h"

struct Screen_t g_Screen = {WIDTH, HEIGHT, (unsigned*)0xA0100000, 320*240*2};

void drawTri(Vec3 tri[3]) {
    drawLine(fixdiv(tri[0].x, tri[0].z), fixdiv(tri[0].y, tri[0].z),
             fixdiv(tri[1].x, tri[1].z), fixdiv(tri[1].y, tri[1].z), 0xFE00, g_Screen.framebuffer);
    drawLine(fixdiv(tri[1].x, tri[1].z), fixdiv(tri[1].y, tri[1].z),
             fixdiv(tri[2].x, tri[2].z), fixdiv(tri[2].y, tri[2].z), 0x0FE0, g_Screen.framebuffer);
    drawLine(fixdiv(tri[2].x, tri[2].z), fixdiv(tri[2].y, tri[2].z),
             fixdiv(tri[0].x, tri[0].z), fixdiv(tri[0].y, tri[0].z), 0x00FE, g_Screen.framebuffer);
}

extern uint8_t *framebuffer;
extern unsigned __stdout_index;

Vec3 line = {250,250,10};
Vec3 tri[3] = {{140,140,0x180},{180,140,0x180},{160,180,0x180}};
Vec2 tri2[3] = {{200,170},{240,180},{210,210}};

int main(void)
{
    //float aaa = sinf(0.5f) + cosf(1.25f);

    consoleInit();
    /*initJoypad();*/
    /*screenNTSC(&g_Screen, VI_BPP16);*/

    Joy_t player1_joy, player2_joy;

    while (1) {
        waitScanline(240);
        clock_t t_start = get_ticks_us();
        __stdout_index = 0;
        framebuffer = g_Screen.framebuffer;

        /*updateJoypads();

        readJoypad(0, &player1_joy);
        readJoypad(1, &player2_joy);*/
        line.x += 128;//player1_joy.analog_x;
        line.y += 128;//player2_joy.analog_y;

    puts("1 2 3 foo bar");
    puts("hello world,.123");
    puts("  Hi !@#$%^&*()_+`-=[{\\';/:?\"|}]");

        tri[0].x = 200+(isin(line.x+0x4000)>>7);
        tri[1].y = 120+(isin(line.y+0x2000)>>7);
        tri[1].x = 180+(isin(line.x+0x1000)>>7);
        tri[2].x = 200+(isin(line.x)>>7);
        /*tri[2].x = 200+(sinf(line.x)*10.f);*/

        tri2[0].x = 150+(isin(line.x+0x4000)>>7);
        tri2[0].y = 150+(isin(line.x+0x2000)>>7);
        tri2[1].x = 200+(isin(line.x+0x8000)>>7);
        tri2[1].y = 200+(isin(line.x+0x4000)>>7);
        tri2[2].x = 150+(isin(line.x+0xa000)>>7);
        tri2[2].y = 200+(isin(line.x+0x6000)>>7);

        fillTriangle(tri2, 0xBADA55, g_Screen.framebuffer);
        drawTri(tri);

        for(int i=0x1000;i-=8;) {
            drawLine(100+(isin(i+line.x)>>5)/line.z, 100+(icos(i+line.x)>>5)/line.z, 100, 100, 0xFE00, g_Screen.framebuffer);
        }

        drawCircle(100,100,50,0xF800,g_Screen.framebuffer);
/*
        tri[0].z = fixmul(tri[0].z, 0x104);
        tri[1].z = fixmul(tri[1].z, 0x102);
        tri[2].z = fixmul(tri[2].z, 0x101);
*/

        clock_t t_end = get_ticks_us();
        clock_t dt = t_end - t_start;

        swapFramebuffer(&g_Screen);
        memset(g_Screen.framebuffer,0,g_Screen.size);
    }
    return 0;
}

