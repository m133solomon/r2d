#ifndef COLOR_H
#define COLOR_H

#include <stdlib.h>

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

Color Color_new_rgb(uint8_t r, uint8_t g, uint8_t b);
Color Color_new_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#define COLOR_RED (Color) { 255, 0, 0, 255 }
#define COLOR_GREEN (Color) { 0, 255, 0, 255 }
#define COLOR_BLUE (Color) { 0, 0, 255, 255 }
#define COLOR_YELLOW (Color) { 255, 255, 0, 255 }
#define COLOR_CYAN (Color) { 0, 255, 255, 0 }
#define COLOR_MAGENTA (Color) { 255, 0, 255, 0 }

#endif // COLOR_H
