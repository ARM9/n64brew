#ifndef LIBN64_GL_H
#define LIBN64_GL_H

#include <rcp/rdp.h>
#include <rcp/vi.h>

#ifdef __cplusplus
extern "C" {
#endif

void glInit(void);

void glDrawLine(int x0, int y0, int x1, int y1, uint16_t color);

#ifdef __cplusplus
}
#endif

#endif
