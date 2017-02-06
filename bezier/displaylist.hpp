#pragma once

#include <math.h>
#include <rcp/rdp.h>

/* Display processor command "list" */
struct DisplayList {
    rdp_cmd buffer[512];
    uintptr_t end;
    static const size_t capacity = sizeof(buffer)/sizeof(*buffer);

    DisplayList() : end{0} {}

    DisplayList &swap(uint16_t *fb) {
        rdp_cmd t[] = {set_color_image(IMAGE_DATA_FORMAT_RGBA, SIZE_OF_PIXEL_16B, 320-1, 0x0fffffff&(uintptr_t)fb)};
        memcpy(buffer, t, sizeof(t));
        return *this;
    }

    DisplayList &init() {
        rdp_cmd prologue[] = {
            set_color_image(IMAGE_DATA_FORMAT_RGBA, SIZE_OF_PIXEL_16B, 320-1, 0x00100000)
            ,set_scissor(0, 0, 0, 320<<2, 240<<2)
            ,set_other_modes(CYCLE_TYPE_FILL)
            //,set_fill_color(0x00010001)
            //,fill_rectangle(0, 0, 319<<2, 239<<2)
            ,sync_pipe
        };
        memcpy(buffer, prologue, sizeof(prologue));
        end = sizeof(prologue)/sizeof(*prologue);
        return *this;
    }

    DisplayList &addLines(float *lines, size_t len, uint16_t color) {
        rdp_cmd *buf = buffer + end;

        //*buf++ = sync_pipe;
        *buf++ = set_fill_color((color<<16) | color);
        for(size_t i = 0; i < len/2 - 1; i++) {
            float x1, y1, x2, y2;
            x1 = lines[0]; y1 = lines[1];
            x2 = lines[2]; y2 = lines[3];
            ++++lines;

            float ylf, yhf, xlf, xhf;
            if(y2 > y1) {
                // sort by y
                xlf = x2; xhf = x1;
                ylf = y2; yhf = y1;
            } else if (y1 > y2){
                xlf = x1; xhf = x2;
                ylf = y1; yhf = y2;
            } else if (x2 > x1) {
                // sort by x
                xlf = x2; xhf = x1;
                ylf = y2; yhf = y1;
            } else {
                xlf = x1; xhf = x2;
                ylf = y1; yhf = y2;
            }

            float dxf = xlf - xhf;
            float dyf = ylf - yhf;
            float dxdy = 0.f;
            if(xlf == xhf) {
                xlf += 1.f;
            } else if (ylf == yhf){
                ylf += 1.f;
            } else {
                dxdy = dxf / dyf;
                if(fabsf(dxdy) < 1.f) {
                    xlf = xhf + 1;
                } else {
                    xlf = xhf + fabsf(dxdy);
                }
            }

            int16_t yl, yh; // 11.2 (14 bits) signed fixed point format
            yl = ylf * 4;
            yh = yhf * 4;
            // fractional part of xl and xh as 16 bit "unsigned" fixed point
            // (since the integer part will contain the sign)
            int16_t xli, xhi;
            uint16_t xlifrac, xhifrac;
            xli = (int)xlf;
            xhi = (int)xhf;
            xlifrac = xlf * 65536.f;
            xhifrac = xhf * 65536.f;
            if (dxdy < 0.f && dxdy > -1.f)
                dxdy -= 1.f;
            // fractional part of dxdy as 16 bit fixed point [0.0,1.0)
            int16_t dxdyi;
            uint16_t dxdyifrac;
            dxdyi = (int)dxdy;
            dxdyifrac = dxdy * 65536.f;

            int major_direction = (x1 > x2);
            // assemble rdp command
            rdp_cmd t[] = {fill_triangle(major_direction,0,0,
                    yl,yh,yh, xli,xlifrac, dxdyi,dxdyifrac, xhi,xhifrac, dxdyi,dxdyifrac, 0,0,0,0)};
            // insert command at the end of display list
            memcpy(buf, t, sizeof(t));
            buf += sizeof(t)/sizeof(*t);
        }
        *buf++ = sync_full;
        end = (buf - buffer);
        return *this;
    }
};

