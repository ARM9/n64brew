#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>

//typedef uint16_t pixel;

struct console_t {
    uint16_t *framebuffer;
    int x, y;
    int width, height;
    uint16_t color, bg_color;
    int opaque;                 // 0 = transparent BG, otherwise opaque

    struct {
        uint16_t top, bottom, left, right;
    } margin;

    int line_spacing;
};

#ifdef __cplusplus
extern "C" {
#endif

struct console_t * initConsoleSimple (uintptr_t fb, int width, int height);
void initConsole (struct console_t *c);
void consoleSetColor (uint16_t fg_color, uint16_t bg_color);
void consoleSetFgColor (uint16_t color);
void consoleSetBgColor (uint16_t color);
void consoleSetPos (int x, int y);
void consoleSetX (int x);
void consoleSetY (int y);
void consoleSetOpacity (int o);
void consoleSetMargins(unsigned top, unsigned bottom, unsigned left, unsigned right);
void consoleClear (void);

void putchar (int c);
void print (const char *str);
void printf (const char *fmt, ...);
void puts (const char *str);

#ifdef __cplusplus
}
#endif

#endif
