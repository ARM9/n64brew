#ifndef POLYGON_H
#define POLYGON_H
#include "vector.h"

void edgeDetect(Vec2 v0, Vec2 v1);
void fillTriangle(Vec2 v[3], u16 color, u16 *framebuffer);
void fillTrapezoid(Vec2 v[4], u16 color, u16 *framebuffer);

#endif
