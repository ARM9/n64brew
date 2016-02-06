#ifndef PLOT_H
#define PLOT_H
#include "framebuffer.h"
#include "integer.h"

#define FB_WIDTH    320
#define FB_HEIGHT   240
#define FB_BPP      2

extern struct Framebuffer_t g_Screen;

void drawMeC(void);
void drawMeAsm(void);

#endif
