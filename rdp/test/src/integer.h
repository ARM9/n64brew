#ifndef INTEGER_H
#define INTEGER_H
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

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

#define max(a, b) __builtin_max((a), (b));
#define min(a, b) __builtin_min((a), (b));

#endif
