#include "plot.h"
#include "numbers.h"
#include "vi.h"

inline void plot(int x, int y, u16 color, u16 *framebuffer)
{
    /*__asm__ __volatile__ (
    "sll $v0, %[y1], 7\n"
    "sll %[y1], %[y1], 9\n"
    "addu $t0, $v0, %[y1]\n"
    "sll $v1, %[x1], 1\n"
    "add $t0, $v1\n"
    "add $t0, %[fb]\n"
    "sh %[color], 0($t0)"
    :
    :[x1] "r" (x),
    [y1] "r" (y),
    [color] "r" (color),
    [fb] "r" (framebuffer)
    :"v0", "v1", "t0"
    );*/
    framebuffer[y * FB_WIDTH + x] = color;
}
