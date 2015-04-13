#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vector.h"

void edgeDetect(Vec2 v0, Vec2 v1);
void fillTriangle(Vec2 v[3], unsigned color, unsigned *framebuffer);

#endif //TRIANGLE_H
