#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Framebuffer_t abstraction for VI 8(?)/16/32bpp framebuffers
 *  framebuffer = pointer to a framebuffer in memory
 *  width   = number of pixels in each row (eg scanline)
 *  height  = number of rows in a framebuffer (number of scanlines)
 *  size    = width*height*depth
 *  depth   = number of bytes per pixel
 */
struct Framebuffer_t {
    uint16_t *framebuffer;
    uint32_t width, height, size, depth;
};

void screenNTSC(const struct Framebuffer_t *screen, uint32_t status);
void swapFramebuffer(struct Framebuffer_t *screen);
void waitScanline(uint32_t scanline);
uint32_t getScanline(void);

#ifdef __cplusplus
}
#endif

#endif
