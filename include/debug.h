#ifndef LIBN64_DEBUG_H
#define LIBN64_DEBUG_H

#ifdef __LANGUAGE_ASSEMBLY
// Let the user specify which register to clobber
#ifdef DEBUG
#define BP(r) lui r, 0xAFFF; lbu $0, 0x7FFF(r)
#else
#define BP(r)
#endif

#else

#ifdef DEBUG
#define BP do { \
        int _debug_tmp; \
        __asm__ __volatile__( \
            "lui %0, 0xAFFF\n\t" \
            "lbu $0, 0x7FFF(%0)\n\t" \
            : "=r" (_debug_tmp) \
        ); \
    } while(0)
#else
#define BP
#endif

#endif

#endif
