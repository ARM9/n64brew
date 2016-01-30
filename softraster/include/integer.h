#ifndef INTEGER_H
#define INTEGER_H
#include <stdint.h>

/* not so stdint */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

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
