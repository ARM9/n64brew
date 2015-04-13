#ifndef NUMBERS_H
#define NUMBERS_H
#include <stdint.h>
#include <math.h>

/* not so stdint */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

typedef s32 fixed;

#define FIXED_BITS  8
#define FIXED_ONE   (1<<FIXED_BITS)//0x100
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

#endif //NUMBERS_H
