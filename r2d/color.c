#include "color.h"

Color Color_new_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return (Color) { r, g, b, 255};
}

Color Color_new_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (Color) { r, g, b, a};
}

