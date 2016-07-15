#include "plot.h"
#include <rcp/rdp.h>

rdp_cmd dp_list[] = {
set_scissor(0, 0, 0, 320<<2, 240<<2),
set_other_modes(CYCLE_TYPE_FILL),
//set_z_image(0x00200000),
/*set_color_image(IMAGE_DATA_FORMAT_RGBA, SIZE_OF_PIXEL_16B, 320-1, 0x00200000),*/
set_color_image(IMAGE_DATA_FORMAT_RGBA, SIZE_OF_PIXEL_16B, 320-1, 0x00100000+FB_WIDTH*FB_HEIGHT*FB_BPP),
set_fill_color(0x00010001),
fill_rectangle(0, 0, 319<<2, 239<<2),

/*set_other_modes(SAMPLE_TYPE|BI_LERP_0|ALPHA_DITHER_SEL_NO_DITHER|B_M1A_0_2),*/
/*set_combine_mode(0x0LL,0x00LL, 0LL,0LL, 0x1LL,0x01LL, 0x0LL,0xFLL, 1LL,0LL, 0LL,0LL,0LL, 7LL,7LL,7LL),*/

sync_pipe,
//set_blend_color(0xFF0000FF),
set_fill_color(0xF001F001),
fill_triangle(1,0,0, 400,200,200, 95,0,-1,0, 94,0,-1,0, 0,0,0,0),

//set_color_image(IMAGE_DATA_FORMAT_RGBA, SIZE_OF_PIXEL_16B, 320-1, 0x001000000,
//set_fill_color(0x00010001),
//fill_rectangle(319<<2, 239<<2, 0, 0),

sync_full
};

void drawMeC(void) {
    run_dpc(dp_list, sizeof(dp_list));
}

