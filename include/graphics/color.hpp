#ifndef GRAPHICS_COLOR_HPP
#define GRAPHICS_COLOR_HPP

namespace tung {

struct Color {
    typedef unsigned char uint8_t;

    uint8_t red, green, blue, alpha;

    Color() = default;

    Color(uint8_t r, uint8_t g, uint8_t b) {
        red = r;
        green = g;
        blue = b;
        alpha = 255;
    }

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }

    Color(float r, float g, float b, float a) {
        red = r * 255;
        green = g * 255;
        blue = b * 255;
        alpha = a * 255;
    }

    static const Color RED;
    static const Color WHITE;
    static const Color BLACK;
    static const Color BLUE;
    static const Color GREEN;
};

} // namespace tung

#endif