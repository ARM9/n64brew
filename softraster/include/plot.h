#ifndef PLOT_H
#define PLOT_H
#include "integer.h"

#define FB_WIDTH    320
#define FB_HEIGHT   240
#define FB_BPP      2

extern struct Framebuffer_t g_Screen;

void plot(int x, int y, uint16_t color, uint16_t *framebuffer);
void drawLine(int x1, int y1, int x2, int y2, uint16_t color, uint16_t *framebuffer);
void drawCircle(int x1, int y1, unsigned radius, uint16_t color, uint16_t *framebuffer);

#endif
