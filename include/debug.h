#ifndef LIBN64_DEBUG_H
#define LIBN64_DEBUG_H

#ifdef __LANGUAGE_ASSEMBLY
// Let the user specify which register to clobber
#define BP(r) lui r, 0xAFFF; lbu $0, 0xFFFF(r)
#else
#define BP do { \
        int _debug_tmp; \
        __asm__ __volatile__( \
            "lui %0, 0xAFFF\n\t" \
            "lbu $0, 0x7FFF(%0)\n\t" \
            : "=r" (_debug_tmp) \
        ); \
    } while(0)
#endif

#endif
