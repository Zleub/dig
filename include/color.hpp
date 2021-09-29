#ifndef COLOR_H
#define COLOR_H

struct Color
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
};

Color fromInt(unsigned int color);
int toInt(Color& c);

const Color BLACK = {0, 0, 0, 255};

#endif