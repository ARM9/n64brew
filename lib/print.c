#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <vr4300/cache.h>

#include "print.h"
#include "fonts/torusSans.h"

// 16bpp only, for now...

// todo make buffered probably
/*char out_buffer[(320/8) * (240/8)] = {};*/
/*int row = 0, column = 0;*/

static struct console_t * console;
static struct console_t simple_console;

struct console_t * console_init_simple (uintptr_t p_fb, int fb_width, int fb_height) {
    struct console_t t = {
        .framebuffer = (uint16_t *)p_fb,
        .x = 8,
        .y = 8,
        .width = fb_width,
        .height = fb_height,
        .color = 0xFFFF,
        .bg_color = 0,
        .opaque = 1,
        .margin = {
            .top = 8,
            .bottom = 8,
            .left = 8,
            .right = 8
        },
        .line_spacing = 12
    };
    memcpy(&simple_console, &t, sizeof(struct console_t));
    console = &simple_console;
    return console;
}

// Make sure con doesn't go out of scope
void console_init (struct console_t *con) {
    console = con;
}

void console_set_line_spacing (unsigned s) {
    console->line_spacing = s;
}

void console_set_margins(unsigned top, unsigned bottom, unsigned left, unsigned right) {
    console->margin.top = top;
    console->margin.bottom = bottom;
    console->margin.left = left;
    console->margin.right = right;
}

void console_set_pos (int x, int y) {
    console->x = x;
    console->y = y;
}

void console_set_x (int x) {
    console->x = x;
}
void console_set_y (int y) {
    console->y = y;
}

void console_set_color (uint16_t fg, uint16_t bg) {
    console->color = fg;
    console->bg_color = bg;
}

void console_set_fg_color (uint16_t rgb) {
    console->color = rgb;
}
void console_set_bg_color (uint16_t rgb) {
    console->bg_color = rgb;
}
void console_set_opacity (int o) {
    console->opaque = o;
}

void console_clear () {
    memset(console->framebuffer, console->bg_color, console->width * console->height * 2);
}
void console_flush () {
    writeback_dcache_all();
}

void putchar (int c) {
    if(console->x > console->width - console->margin.right - 8) {
        console->x = console->margin.left;
        console->y += console->line_spacing;
    }
    if(console->y >= console->height - console->margin.bottom - 8) {
        console->y = console->margin.top;
    }

    /*if (c == ' ') {*/
        /*console->x += 8;*/
        /*return;*/
    /*} else*/
    if (c == '\n') {
        console->x = console->margin.left;
        console->y += console->line_spacing;
        return;
    } else if (c == '\t') {
        for(int i = 0; i < 4; i++)
            putchar(' ');
        //console->x += 8*4;
        return;
    }
    /*c &= 0x7f;*/
    c -= 32;
    c *= 8;

    // TODO make fonts 1bpp or 8bpp sequences of rows instead of 16bpp tiles
    uint16_t *fb = console->framebuffer;

    if (console->opaque) {
        for(int y = 0; y < 8; y++) {
            for(int x = 0; x < 8; x++) {
                int pixel = torusSansBitmap[c + x + y * 768];

                uint16_t color = pixel == 0x0001 ? console->bg_color : console->color;

                fb[console->x + x + (console->y + y)*console->width] = color;
            }
        }
    } else {
        for(int y = 0; y < 8; y++) {
            for(int x = 0; x < 8; x++) {
                int pixel = torusSansBitmap[c + x + y * 768];

                if (pixel == 0x0001)
                    continue;
                uint16_t color = console->color;

                fb[console->x + x + (console->y + y)*console->width] = color;
            }
        }
    }
    console->x += 8;
}

void _unimplemented_fmt (char * fmt) {
    uint16_t pfg = console->color, pbg = console->bg_color;
    console->color = 0xf800; console->bg_color = 0;
    print("\nInvalid fmt: ");
    putchar('%');
    puts(fmt);
    console->color = pfg; console->bg_color = pbg;
}

void printf (const char *fmt, ...) {
    va_list arg;

    char buf[64];

    int i;
    char c;

    va_start(arg, fmt);

    while ((c = *fmt++)) {
        if (c != '%') {
            putchar(c);
            continue;
        }
        c = *fmt++;
        switch(c) {
            /*
            case '0': {
                %04x format
            }
                break;
            */
            /*
            case '*': {
                printf("%*x", width, 0x1234)
            }
                break;
            */
            case 'c':
                i = va_arg(arg, int);
                putchar(i);
                break;
            case 'd':
                i = va_arg(arg, int);
                itoa(i, buf, 10);
                print(buf);
                break;
            case 'x':
                i = va_arg(arg, int);
                itoa(i, buf, 16);
                print(buf);
                break;
            case 'b': // non standard? sod it
                i = va_arg(arg, int);
                itoa(i, buf, 2);
                print(buf);
                break;
            /*
            case 'f': {
                todo print floats
            }
                break;
            */
            case 'l': {
                c = *fmt++;
                if (c != 'l') {
                    char buf[] = {'l',c,0};
                    _unimplemented_fmt(buf);
                    va_end(arg);
                    return;
                }
                c = *fmt++;
                switch (c) {
                int64_t li;
                    case 'd':
                        li = va_arg(arg, int64_t);
                        lltoa(li, buf, 10);
                        print(buf);
                        break;
                    case 'x':
                        li = va_arg(arg, int64_t);
                        lltoa(li, buf, 16);
                        print(buf);
                        break;
                    default: {
                        char buf[] = {'l','l',c,0};
                        _unimplemented_fmt(buf);
                        va_end(arg);
                        return;
                    }
                }
            }
                break;
            case 's': {
                char *s = va_arg(arg, char *);
                print(s);
            }
                break;
            case '%':
                putchar('%');
                break;
            case 0: // prevent buffer overrun on string ending in "...%"
                fmt--;
                break;
            default: {
                char buf[] = {c,0};
                _unimplemented_fmt(buf);
                va_end(arg);
                return;
            }
        }
    }
    va_end(arg);
}

void print (const char *str) {
    char c;
    while ((c = *str++)) {
        putchar(c);
    }
}

void puts (const char *str) {
    print(str);
    putchar('\n');
}

