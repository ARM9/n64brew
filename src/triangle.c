#include "triangle.h"
#include "plot.h"
#include "vi.h"

void sort_vertices_asc_y(Vec2 v[3])
{
    Vec2 vtmp;
    if(v[0].y > v[1].y){
        vtmp = v[0];
        v[0] = v[1];
        v[1] = vtmp;
    }
    if(v[0].y > v[2].y){
        vtmp = v[0];
        v[0] = v[2];
        v[2] = vtmp;
    }
    if(v[1].y > v[2].y){
        vtmp = v[1];
        v[1] = v[2];
        v[2] = vtmp;
    }
}

void drawHorizontalLine(int x1, int y1, int x2, unsigned color, unsigned *framebuffer)
{
    for(;x2 <= x1; x2++){
        plot(x2, y1, color, framebuffer);
    }
}

void fill_flat_bottom_triangle(Vec2 vt0, Vec2 vt1, Vec2 vt2, unsigned color)
{
    float slope1 = (float)(vt1.x - vt0.x) / (float)(vt1.y - vt0.y);
    float slope2 = (float)(vt2.x - vt0.x) / (float)(vt2.y - vt0.y);

    float x1 = vt0.x;
    float x2 = vt0.x + 0.5f;

    for (int scanlineY = vt0.y; scanlineY <= vt1.y; scanlineY++)
    {
        drawHorizontalLine((int)x1, scanlineY, (int)x2, color, g_Screen.framebuffer);
        x1 += slope1;
        x2 += slope2;
    }
}

void fill_flat_top_triangle(Vec2 vt0, Vec2 vt1, Vec2 vt2, unsigned color)
{
    float slope1 = (float)(vt2.x - vt0.x) / (float)(vt2.y - vt0.y);
    float slope2 = (float)(vt2.x - vt1.x) / (float)(vt2.y - vt1.y);

    float x1 = vt2.x;
    float x2 = vt2.x + 0.5f;

    for (int scanlineY = vt2.y; scanlineY > vt0.y; scanlineY--)
    {
        x1 -= slope1;
        x2 -= slope2;
        drawHorizontalLine((int)x1, scanlineY, (int)x2, color, g_Screen.framebuffer);
    }
}

void fillTriangle(Vec2 tri[3], unsigned color)
{
    Vec2 vt0, vt1, vt2, vt3;

    sort_vertices_asc_y(tri);
    vt0 = tri[0];
    vt1 = tri[1];
    vt2 = tri[2];

    if(vt1.y == vt2.y){
        fill_flat_bottom_triangle(vt0, vt1, vt2, color);
    }else if(vt0.y == vt1.y){
        fill_flat_top_triangle(vt0, vt1, vt2, color);
    }else{
    int t = (int)(vt0.x + ((float)(vt1.y - vt0.y) / (float)(vt2.y - vt0.y)) * (vt2.x - vt0.x));
    vt3.x = t;
    vt3.y = vt1.y;
    fill_flat_bottom_triangle(vt0, vt1, vt3, color);
    fill_flat_top_triangle(vt1, vt3, vt2, color);
    }
}

