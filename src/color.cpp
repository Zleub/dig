#include <color.hpp>

Color fromInt(int color) {
    return {
        .r = color & 0x000000FFu,
        .g = (color & 0x0000FF00u) >> 8,
        .b = (color & 0x00FF0000u) >> 16,
        .a = (color & 0xFF000000u) >> 24
    };
}

int toInt(Color& c) {
    return c.r + (c.g << 8) + (c.b << 16) + (c.a << 24);
}