#ifndef PLOT_H
#define PLOT_H
#include "numbers.h"

extern void plot(int x, int y, uint16_t color, uint16_t *framebuffer);
extern void drawLine(int x1, int y1, int x2, int y2, uint16_t color, uint16_t *framebuffer);
extern void drawCircle(int x1, int y1, unsigned radius, uint16_t color, uint16_t *framebuffer);

#endif //PLOT_H
