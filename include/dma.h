#ifndef LIBN64_DMA_H
#define LIBN64_DMA_H
#include <stdint.h>

void dmaCartToDram(void *dest, const void *src, uint32_t len);

#endif
