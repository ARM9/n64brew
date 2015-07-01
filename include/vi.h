#ifndef VI_H
#define VI_H
#include "numbers.h"

#define WIDTH 320
#define HEIGHT 240

/* VI */
#define VI_BPP0 0x0000 // VI Status/Control: Color Depth Blank (No Data Or Sync) (Bit 0..1)
#define VI_BPP16 0x0002 // VI Status/Control: Color Depth 16BPP R5/G5/B5/A1 (Bit 0..1)
#define VI_BPP32 0x0003 // VI Status/Control: Color Depth 32BPP R8/G8/B8/A8 (Bit 0..1)

struct Screen_t {
    u32 width, height;
    u16 *framebuffer;
    u32 size;
};

extern struct Screen_t g_Screen;

extern void screenNTSC(const struct Screen_t *screen, u32 status);
extern void swapFramebuffer(struct Screen_t *screen);
extern void waitScanline(u32 scanline);

#endif //VI_H
