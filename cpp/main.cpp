#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <time.h>
#include <rcp/rdp.h>
#include <rcp/vi.h>
#include <vr4300/cache.h>

#include "framebuffer.h"

template <uint8_t R, uint8_t G, uint8_t B>
struct RGBFactory {
    enum : uint16_t { color = R>>3<<11 | G>>3<<6 | B>>3<<1 };
};

template<typename T>
struct ZBuffer {
    ZBuffer(T *zbuffer, size_t width, size_t height) :
         m_zbuffer(zbuffer)
        ,m_width(width), m_height(height)
        ,m_size(m_width * m_height)
    {
    }
    ~ZBuffer() {}

private:
    T *m_zbuffer;
    const size_t m_width, m_height;
    const size_t m_size;
};

template<typename T>
struct Framebuffer {
    Framebuffer(T *fb, size_t width, size_t height) :
         m_framebuffer(fb)
        ,m_width(width), m_height(height)
        ,m_Bpp(sizeof(T))
        ,m_size(m_width*m_height*m_Bpp)
    {
        static_assert(sizeof(T*) == 4, "Use -mabi=o64 -mlong32");
    }
    ~Framebuffer() {}

    void plot(unsigned x, unsigned y, T color) const {
        m_framebuffer[y * m_width + x] = color;
    }

    void swap() {
        *VI_ORIGIN = (uint32_t)m_framebuffer;
        m_framebuffer = (T*) ((uintptr_t)m_framebuffer ^ m_size);
    }

    size_t getWidth() const { return m_width; }
    size_t getHeight() const { return m_height; }
    size_t getBpp() const { return m_Bpp; }
    size_t getSize() const { return m_size; }
private:
    T *m_framebuffer;
    const size_t m_width, m_height, m_Bpp;
    const size_t m_size;
};

static vi_state_t vi_state = {
	VI_BPP16 \
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

rdp_cmd dp_list[] = {
set_scissor(0, 0, 0, 320<<2, 240<<2),
set_other_modes(CYCLE_TYPE_FILL),
set_color_image(IMAGE_DATA_FORMAT_RGBA, SIZE_OF_PIXEL_16B, 320-1, 0x00100000),
//set_fill_color(0x00010001),
//fill_rectangle(0, 0, 319<<2, 239<<2),

sync_pipe,
set_fill_color(0xF001F001),
fill_triangle(RIGHT_MAJOR,0,0, 400,300,200, 150,0,0,24576, 120,0,0,39322, 110,0,0,24030),

sync_full
};

//ZBuffer<uint16_t> myZb((uint16_t*)0x80100000+myFb.getSize()*2, 320, 240);

int main(void) {
    Framebuffer<uint16_t> myFb(reinterpret_cast<uint16_t*>(0x80100000), 320, 240);

    vi_flush_state(&vi_state);

    uint16_t c = RGBFactory<0,255,0>::color;
    while (1) {
        for(unsigned x = 0; x < myFb.getWidth(); x++) {
            waitScanline(myFb.getHeight());

            for(unsigned y = 0; y < myFb.getHeight(); y++) {
                myFb.plot(x+y, y, c ^ y*x);
            }

            writeback_dcache_all();

            run_dpc(dp_list, sizeof(dp_list));
            myFb.swap();
        }
        c ^= clock();
    }
    return 0;
}
