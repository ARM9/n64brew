#include <stdint.h>
#include <string.h>
#include <mmio.h>
#include <rcp/rsp.h>
#include <rcp/vi.h>

#include "print.h"

extern char ucode[0x1000];
extern char ucode_data[0x1000];
extern unsigned ucode_data_len;

#define Framebuffer 0x00100000

int main(void)
{
    rsp_init();
    rsp_load(&ucode, 0x1000, 0xfff);
    rsp_load(&ucode_data, 0x0000, ucode_data_len);

    console_init_simple(KSEG0(Framebuffer), 320, 240);

    vi_state_t vi_state;
    vi_setup_res(VI_RES_320x240, &vi_state);
    vi_state.status |= VI_BPP16;
    vi_state.origin = Framebuffer;
    vi_flush_state(&vi_state);


    while (1) {
        rsp_run(0);
        while(rsp_busy());

        vs16 *dmem = (vs16*)RSP_DMEM;
        console_set_pos(8,8);
        printf ("%d\n%d\n%d\n%d\n", dmem[0], dmem[1], dmem[2], dmem[3]);
        printf ("%d\n%d\n%d\n%d", dmem[4], dmem[5], dmem[6], dmem[7]);
        console_flush();

        vi_wait_scanline(240);
    }
    return 0;
}
