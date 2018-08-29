#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <rcp/rdp.h>
#include <rcp/vi.h>
#include <vr4300/cache.h>

#include "framebuffer.h"
#include "fixed_point.hpp"
#include "bezier.hpp"
#include "displaylist.hpp"

static_assert(sizeof(void*) == 4, "Use -mabi=eabi -mlong32");

constexpr uint16_t RGB15(unsigned R, unsigned G, unsigned B) {
    return ((R & 0x1f)<<11 | (G & 0x1f)<<6 | (B & 0x1f)<<1);
}
constexpr uint16_t RGBA15(unsigned R, unsigned G, unsigned B, unsigned A) {
    return ((R & 0x1f)<<11 | (G & 0x1f)<<6 | (B & 0x1f)<<1 | (A & 1));
}
constexpr uint32_t RGB32(unsigned R, unsigned G, unsigned B) {
    return ((R & 0xff)<<16 | (G & 0xff)<<8 | (B & 0xff));
}

template<typename T>
struct Framebuffer {
    static const unsigned Bpp = sizeof(T);

    Framebuffer(T *fb, size_t width, size_t height) :
         m_framebuffer(fb)
        ,m_width(width), m_height(height)
        ,m_size(m_width*m_height*Bpp)
    {
    }
    ~Framebuffer() {}

    inline void plot(unsigned x, unsigned y, T color) {
        m_framebuffer[y * m_width + x] = color;
    }

    void drawLine(int x1, int y1, int x2, int y2, T color) {
        int e, inc1, inc2;

        int x = x1;
        int y = y1;

        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);

        int incx = (x2 < x1 ? -1 : 1);
        int incy = (y2 < y1 ? -1 : 1);

        plot(x, y, color);
        if(dx > dy) {
            e = 2 * dy - dx;
            inc1 = 2 * (dy - dx);
            inc2 = 2 * dy;
            for(int i = 0; i < dx; i++) {
                if(e >= 0) {
                    y += incy;
                    e += inc1;
                } else {
                    e += inc2;
                }
                x += incx;
                plot(x, y, color);
            }
        } else {
            e = 2 * dx - dy;
            inc1 = 2 * (dx - dy);
            inc2 = 2 * dx;
            for(int i = 0; i < dy; i++) {
                if(e >= 0) {
                    x += incx;
                    e += inc1;
                } else {
                    e += inc2;
                }
                y += incy;
                plot(x, y, color);
            }
        }
    }

    void swap() {
        *VI_ORIGIN = (uint32_t)m_framebuffer;
        m_framebuffer = (T*) ((uintptr_t)m_framebuffer ^ m_size);
    }

    void clear(T color) {
        for(size_t i = 0; i < m_width * m_height; i++) {
            m_framebuffer[i] = color;
        }
    }

    size_t width() const { return m_width; }
    size_t height() const { return m_height; }
    size_t size() const { return m_size; }
//private:
    T *m_framebuffer;
    const size_t m_width, m_height;
    const size_t m_size;
};

static vi_state_t vi_state = {
	VI_BPP16
        | GAMMA_EN|GAMMA_DITHER_EN|INTERLACE|AA_MODE_2|PIXEL_ADV_3, // status
	0x00100000, // origin
	0x00000140, // width
	0x00000200, // intr
	0x00000000, // current
	0x03E52239, // burst
	0x0000020D, // v_sync
	0x00000C15, // h_sync
	0x0C150C15, // leap
	0x006C02EC, // h_start
	0x002501FF, // v_start
	0x000E0204, // v_burst
	0x00000200, // x_scale
	0x00000400, // y_scale
};

rdp_cmd dp_list[512];// = {
//set_fill_color(0xF001F001)
//,fill_triangle(RIGHT_MAJOR,0,0, 400,300,200, 150,0,0,24576, 120,0,0,39322, 110,0,0,24030)

//,sync_full
//};

//template<int s> struct print_size;
//print_size<sizeof(DisplayList)> tttttttt;

//float lines[] = {10,10,50,50,60,10,100,100};

static_assert(sizeof(Vec2<float>[10]) == 8*10, "vec2 float not 8 bytes");
Vec2<float> rdplines[10];

int main(void) {
    Framebuffer<uint16_t> myFb(reinterpret_cast<uint16_t*>(0x8010'0000), 320, 240);

    vi_flush_state(&vi_state);

    Bezier<1> linear = {{ {10.f,20.f}, {200.f,50.f} }};
    Bezier<2> quadratic = {{ {220.f, 100.f}, {100.f, 0.f}, {130.f, 80.f} }};
    Bezier<3> cubic = {{ {120.f,44.f}, {222.f,147.f}, {15.f,64.f}, {157.f,196.f} }};

    unsigned i = 0;
    for(float t = 0.f; t < 1.f; t += 0.1f) {
        rdplines[i++] = quadratic.draw(t);
    }
    DisplayList dpl;
    dpl.init().addLines((float*)rdplines, 2*sizeof(rdplines)/sizeof(*rdplines), 0xf800);

    f24_8 x = 20.f;
    Fixed<short, 4> test{100.f};

    while (1) {

        auto bounce = [] (float p, int range, float scale) {
            return (float)((int)p % (range+1) - range/2) * scale;
        };
        quadratic.points[0].x += bounce(x, 240, .02f);
        quadratic.points[0].y += bounce(x, 80, .09f);
        quadratic.points[1].x += bounce(x, 100, .1f);
        quadratic.points[1].y -= bounce(x, 300, .01f);
        quadratic.points[2].x -= bounce(x, 120, .06f);
        quadratic.points[2].y += bounce(x, 100, .08f);

        for(float t = 0.0f; t <= 1.0f; t += 0.05f) {
            auto p1 = linear.draw(t);
            auto p2 = linear.draw(t+0.05f);
            myFb.drawLine(p1.x, p1.y, p2.x, p2.y, 0x33fe);

            p1 = quadratic.draw(t);
            p2 = quadratic.draw(t+0.05f);
            myFb.drawLine(p1.x, p1.y, p2.x, p2.y, 0x03e6);

            p1 = cubic.draw(t);
            p2 = cubic.draw(t+0.05f);
            myFb.drawLine(p1.x, p1.y, p2.x, p2.y, 0x33fe);
        }

        Vec2<Fixed<short,4>> fp1{10.5f, 100.7f}, fp2{160.f, 131.1f};
        //myFb.drawLine(fp1.x, fp1.y, fp2.x, fp2.y, RGB15(17,5,14));

        x += f24_8{0.5f};
        //test += .5f;
        test += 0x08;
        myFb.plot((int)-test % myFb.width(), 200, 0xf000);

        writeback_dcache_all(); // flush dcache because framebuffer is in ram
        rdp_exec(dpl.buffer, dpl.end*sizeof(rdp_cmd));

        //for(i = 0; i < 100000; i++)
            //asm volatile("":::"memory");
        /*uint32_t scanline = getScanline();
        while(scanline<235){
            scanline = getScanline();
        }
        myFb.drawLine(0, scanline, 10, scanline, RGB15(31,0,0));*/

        waitScanline(myFb.height());    // wait for vblank
        myFb.swap();                    // then swap the framebuffers (actually page flip)
        dpl.swap(myFb.m_framebuffer);   // make display list point to the back buffer
        myFb.clear(0x96bc);             // clear back buffer
    }
    return 0;
}

