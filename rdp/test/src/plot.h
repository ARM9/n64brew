#ifndef PLOT_H
#define PLOT_H
#include <stdint.h>
#include "framebuffer.h"

#define Framebuffer 0x00100000
#define FB_WIDTH 320
#define FB_HEIGHT 240
#define FB_BPP 2

extern struct Framebuffer_t g_Screen;

void drawMeC(void);
void drawMeAsm(void);

#endif
