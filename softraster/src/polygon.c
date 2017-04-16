#include "integer.h"
#include "plot.h"
#include "polygon.h"
#include "vector.h"

short g_EdgeBufferL[FB_HEIGHT];
short g_EdgeBufferR[FB_HEIGHT];

void edgeDetect(Vec2 v0, Vec2 v1)
{
    fixed x1 = v0.x,
        x2 = v1.x,
        y1 = v0.y,
        y2 = v1.y;

    short *edge = g_EdgeBufferL;

    if(y1 > y2) {
        edge = g_EdgeBufferR;
        fixed tmp = x1;
        x1 = x2;
        x2 = tmp;
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    fixed dx;
    if(y1 != y2){
        dx = fixdiv(i2f(x2 - x1), i2f(y2 - y1));
    } else {
        return;
    }
    
    x1 = i2f(x1);
    for(int y = y1; y <= y2; y++){
        if(y >= FB_HEIGHT)
            break;
        if(y >= 0){
            int tx = f2i(x1);
            edge[y] = imax(0, imin(FB_WIDTH-1, tx));
        }
        x1 += dx;
    }
}

int clipTriangle(Vec2 v[3]) {
    if(v[0].x < 0) {
        if(v[1].x < 0 && v[2].x < 0)
            return 1;
    }
    if(v[0].y < 0) {
        if(v[1].y < 0 && v[2].y < 0)
            return 1;
    }
    if(v[0].x >= FB_WIDTH) {
        if(v[1].x >= FB_WIDTH && v[2].x >= FB_WIDTH)
            return 1;
    }
    /*if(v[0].y >= FB_HEIGHT) {
      covered in edgeDetect
    }*/
    return 0;
}

int backfaceCullTriangle(Vec2 v[3]) {
    fixed determinant =
          (v[0].x * v[1].y - v[1].x * v[0].y)
        + (v[1].x * v[2].y - v[2].x * v[1].y)
        + (v[2].x * v[0].y - v[0].x * v[2].y);
    return determinant > 0;
}

void fillTriangle(Vec2 v[3], u16 color, u16 *framebuffer)
{
    if(clipTriangle(v) || backfaceCullTriangle(v))
        return;
    int max_y = imax(0, imin(FB_HEIGHT, imax(v[0].y, imax(v[1].y, v[2].y))));
    int min_y = imax(0, imin(FB_HEIGHT, imin(v[0].y, imin(v[1].y, v[2].y))));

    edgeDetect(v[0], v[1]);
    edgeDetect(v[1], v[2]);
    edgeDetect(v[2], v[0]);

    for(int y = min_y; y <= max_y; y++){
        for(int x = g_EdgeBufferL[y]; x <= g_EdgeBufferR[y]; x++)
            plot(x, y, color, framebuffer);
    }
}

// concave quadrilaterals not allowed
