#include <stdint.h>
#include <string.h>
#include <mmio.h>
#include <rcp/rsp.h>

extern char ucode_start[0x1000];

int main(void)
{
    rsp_init();
    rsp_run(&ucode_start);

    while (1) {
    }
    return 0;
}
