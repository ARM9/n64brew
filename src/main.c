#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "libn64.h"
#include "dma.h"
#include "numbers.h"
#include "plot.h"
#include "vi.h"

typedef struct vec2 {
    int x, y;
} vec2;

typedef struct vec3 {
    int x, y, z;
} vec3;

typedef vec3 triangle[3];

void drawTri(vec3 tri[3]) {
    drawLine(fixdiv(tri[0].x, tri[0].z), fixdiv(tri[0].y, tri[0].z),
             fixdiv(tri[1].x, tri[1].z), fixdiv(tri[1].y, tri[1].z), 0xFE00, g_Screen.framebuffer);
    drawLine(fixdiv(tri[1].x, tri[1].z), fixdiv(tri[1].y, tri[1].z),
             fixdiv(tri[2].x, tri[2].z), fixdiv(tri[2].y, tri[2].z), 0x0FE0, g_Screen.framebuffer);
    drawLine(fixdiv(tri[2].x, tri[2].z), fixdiv(tri[2].y, tri[2].z),
             fixdiv(tri[0].x, tri[0].z), fixdiv(tri[0].y, tri[0].z), 0x00FE, g_Screen.framebuffer);
}

extern uint8_t *framebuffer;
extern unsigned __stdout_index;
int main(void)
{
    //float aaa = sinf(0.5f) + cosf(1.25f);

    consoleInit();
    /*screenNTSC(&g_Screen, VI_BPP16);*/

    vec3 line = {250,250,10};
    triangle tri = {{140,140,0x180},{180,140,0x180},{160,180,0x180}};

    while (1) {
        waitScanline(240);
        clock_t t_start = get_ticks_us();
        __stdout_index = 0;
        framebuffer = g_Screen.framebuffer;
    puts("1 2 3 foo bar");
    puts("hello world,.123");
    puts("  Hi !@#$%^&*()_+`-=[{\\';/:?\"|}]");

        drawTri(tri);
        for(int i=0x1000;i-=8;) {
            drawLine(100+(isin(i+line.x)>>5)/line.z, 100+(icos(i+line.x)>>5)/line.z, 100, 100, 0xFE00, g_Screen.framebuffer);
        }

        drawCircle(100,100,50,0xF800,g_Screen.framebuffer);

        line.x += 128;

        tri[0].x = 200+(isin(line.x+0x4000)>>7);
        tri[1].y = 120+(isin(line.x+0x2000)>>7);
        tri[1].x = 180+(isin(line.x+0x1000)>>7);
        tri[2].x = 200+(isin(line.x)>>7);
/*
        tri[0].z = fixmul(tri[0].z, 0x104);
        tri[1].z = fixmul(tri[1].z, 0x102);
        tri[2].z = fixmul(tri[2].z, 0x101);
*/
        drawLine(161,120,161,120,0x7ffe, g_Screen.framebuffer);
        plot(160,120,0x7ffe,g_Screen.framebuffer);
        plot(160,121,0x7ffe,g_Screen.framebuffer);
        plot(160,122,0x7ffe,g_Screen.framebuffer);

        clock_t t_end = get_ticks_us();
        clock_t dt = t_end - t_start;

        swapFramebuffer(&g_Screen);
        memset(g_Screen.framebuffer,0,g_Screen.size);
    }
    return 0;
}

