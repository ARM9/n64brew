#ifndef LIBN64_INPUT_H
#define LIBN64_INPUT_H

#include <rcp/pif.h>

#define JOY_CRIGHT  0x1 // PIF HWORD: CAMERA RIGHT
#define JOY_CLEFT   0x2 // PIF HWORD: CAMERA LEFT
#define JOY_CDOWN   0x4 // PIF HWORD: CAMERA DOWN
#define JOY_CUP     0x8 // PIF HWORD: CAMERA UP
#define JOY_R       0x10 // PIF HWORD: R (PAN RIGHT)
#define JOY_L       0x20 // PIF HWORD: L (PAN LEFT)
#define JOY_RIGHT   0x100 // PIF HWORD: RIGHT
#define JOY_LEFT    0x200 // PIF HWORD: LEFT
#define JOY_DOWN    0x400 // PIF HWORD: DOWN
#define JOY_UP      0x800 // PIF HWORD: UP
#define JOY_START   0x1000 // PIF HWORD: START
#define JOY_Z       0x2000 // PIF HWORD: Z
#define JOY_B       0x4000 // PIF HWORD: B
#define JOY_A       0x8000 // PIF HWORD: A

/* C interface */
#ifndef __LANGUAGE_ASSEMBLY
#include <stdint.h>

typedef struct {
    uint16_t buttons;
    int8_t analog_x, analog_y;
} Joypad_t;

void initJoypad();
void updateJoypads();
void readJoypad(unsigned pad_num, Joypad_t *joypad);
#endif

#endif
