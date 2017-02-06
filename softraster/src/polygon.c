#include "integer.h"
#include "plot.h"
#include "polygon.h"
#include "vector.h"

int g_EdgeBufferL[FB_HEIGHT + 1];
int g_EdgeBufferR[FB_HEIGHT + 1];

void edgeDetect(Vec2 v0, Vec2 v1)
{
    fixed x1 = i2f(v0.x),
        x2 = i2f(v1.x),
        y1 = i2f(v0.y),
        y2 = i2f(v1.y);

    if(y1 > y2){
        fixed tmp = x1;
        x1 = x2;
        x2 = tmp;
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    fixed dx;
    if(y1 == y2){
        dx = 0;
    }else{
        dx = fixdiv((x2 - x1), (y2 - y1));
    }
    
    for(int i = f2i(y1); i <= f2i(y2); i++){
        if(i > 0 && i < FB_HEIGHT){
            int tx = f2i(x1);
            if(tx < g_EdgeBufferL[i])
                g_EdgeBufferL[i] = imax(0, tx);
            if(tx > g_EdgeBufferR[i])
                g_EdgeBufferR[i] = imin(FB_WIDTH, tx);
        }
        x1 += dx;
    }
}

void fillTriangle(Vec2 v[3], u16 color, u16 *framebuffer)
{
    int max_y = imax(0, imin(FB_HEIGHT, imax(v[0].y, imax(v[1].y, v[2].y))));
    int min_y = imax(0, imin(FB_HEIGHT, imin(v[0].y, imin(v[1].y, v[2].y))));

    for(int i = min_y; i < max_y; i++){
        g_EdgeBufferL[i] = FB_WIDTH;
        g_EdgeBufferR[i] = 0;
    }

    edgeDetect(v[0], v[1]);
    edgeDetect(v[1], v[2]);
    edgeDetect(v[2], v[0]);

    for(int y = min_y; y < max_y; y++){
        if(g_EdgeBufferL[y] <= g_EdgeBufferR[y])
            for(int x = g_EdgeBufferL[y]; x < g_EdgeBufferR[y]; x++)
                plot(x, y, color, framebuffer);
    }
}

// concave trapezoids not allowed
