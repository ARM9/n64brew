#include "dma.h"
#include "pi.h"

void dmaCartToDram(void *dest, const void *src, uint32_t len) {
    while(*PI_STATUS & 3) {}
    *PI_DRAM_ADDR = (uint32_t)dest & 0x7FFFFF;
    *PI_CART_ADDR = 0x10000000 | ((uint32_t)src & 0x3FFFFFF);
    *PI_WR_LEN = len-1;
}

