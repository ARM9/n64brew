#include "numbers.h"
#include "plot.h"
#include "triangle.h"
#include "vector.h"
#include "vi.h"

int g_EdgeBufferL[HEIGHT + 1];
int g_EdgeBufferR[HEIGHT + 1];

void edgeDetect(Vec2 v0, Vec2 v1)
{
    float x1 = v0.x,
        x2 = v1.x,
        y1 = v0.y,
        y2 = v1.y;

    if(y1 > y2){
        float tmp = x1;
        x1 = x2;
        x2 = tmp;
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    float dx;
    if(y1 == y2){
        dx = x2 - x1;
    }else{
        dx = (x2 - x1) / (y2 - y1);
    }

    for(int i = y1; i <= y2; i++){
        if(x1 < g_EdgeBufferL[i])
            g_EdgeBufferL[i] = x1;
        if(x1 > g_EdgeBufferR[i])
            g_EdgeBufferR[i] = x1;
        x1 += dx;
    }
}

void fillTriangle(Vec2 v[3], unsigned color, unsigned *framebuffer)
{
    // possibly faster to just not sort the vectors to find min/max y
    int max_y = max(v[0].y, max(v[1].y, v[2].y));
    int min_y = min(v[0].y, min(v[1].y, v[2].y));

    for(int i = min_y; i < max_y; i++){
        g_EdgeBufferL[i] = WIDTH;
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

