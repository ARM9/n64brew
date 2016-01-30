#include <stdint.h>
#include <rcp/rdp.h>

void runDPC(const void * list, uint32_t len) {
    uint32_t end = (uint32_t)list+len;
    __builtin_memcpy((void*)DPC_START, &list, 4);
    __builtin_memcpy((void*)DPC_END, &end, 4);
    //*DPC_START = (unsigned)list;
    //*DPC_END = (unsigned)list + len;
}
