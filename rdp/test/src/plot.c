#include "plot.h"
#include <rcp/rdp.h>

static unsigned long long dp_list[] = {



set_scissor(0, 0, 0, 320<<2, 240<<2),
set_other_modes(CYCLE_TYPE_FILL),
set_color_image(IMAGE_DATA_FORMAT_RGBA, SIZE_OF_PIXEL_16B, 320-1, Framebuffer),
set_fill_color(0x00010001),
fill_rectangle(0, 0, 319<<2, 239<<2),
sync_pipe,
set_fill_color(0xF001F001),
fill_triangle(1,0,0, 400,200,200, 95,0,-1,0, 94,0,-1,0, 0,0,0,0),
sync_full
};

void drawMeC(void) {
    rdp_exec(dp_list, sizeof(dp_list));
}

