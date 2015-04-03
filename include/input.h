#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

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

typedef struct Joy_t {
    uint16_t buttons;
    int8_t analog_x, analog_y;
}Joy_t;

void initJoypad();
void readJoypad(Joy_t *joypad);

#endif //INPUT_H
