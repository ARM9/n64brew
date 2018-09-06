#ifndef INTEGER_H
#define INTEGER_H
#include <stdint.h>

/* not so stdint */
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define imax(a, b) (a - ((a-b) & (a-b)>>31))
#define imin(a, b) (b + ((a-b) & (a-b)>>31))

typedef s32 fixed;

#define FIXED_BITS  8
#define FIXED_ONE   (1<<FIXED_BITS) //0x100
#define FIXED_HALF  ((1<<FIXED_BITS)>>1)

#define f2i(A) ((A) >> FIXED_BITS)
#define i2f(A) ((A) << FIXED_BITS)

#define fixmul(A,B) f2i((A)*(B))
#define fixdiv(A,B) (i2f(A)/(B))

#define fixceil(A) f2i((A)+(FIXED_ONE-1))
#define fixinv(A) fixdiv(FIXED_ONE,(A))

int isin(int x);

inline static int icos(int x) {
    return isin(x + 0x2000);
}

short sqrt16(short x);

#endif
