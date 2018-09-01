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

struct console_t * console_init_simple (uintptr_t fb, int width, int height);
void console_init (struct console_t *c);
void console_set_color (uint16_t fg_color, uint16_t bg_color);
void console_set_fg_color (uint16_t color);
void console_set_bg_color (uint16_t color);
void console_set_pos (int x, int y);
void console_set_x (int x);
void console_set_y (int y);
void console_set_opacity (int o);
void console_set_margins(unsigned top, unsigned bottom, unsigned left, unsigned right);
void console_clear (void);
void console_flush (void);

void putchar (int c);
void print (const char *str);
void printf (const char *fmt, ...);
void puts (const char *str);

#ifdef __cplusplus
}
#endif

#endif
