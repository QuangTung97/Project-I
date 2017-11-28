#ifndef GRAPHICS_COLOR_HPP
#define GRAPHICS_COLOR_HPP

namespace tung {

// Class đại diện cho một màu hiển thị. 
struct Color {
    typedef unsigned char uint8_t;

    uint8_t red, green, blue, alpha;

    Color() = default;

    // constructor: 
    // @r, b, g: Lần lượt là đỏ, xanh lá cây và xanh dương. 
    Color(uint8_t r, uint8_t g, uint8_t b) {
        red = r;
        green = g;
        blue = b;
        alpha = 255;
    }

    // constructor: 
    // @r, b, g: Lần lượt là đỏ, xanh lá cây và xanh dương. 
    // @a: Màu alpha - thể hiện độ trong suốt. 
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        red = r;
        green = g;
        blue = b;
        alpha = a;
    }

    // constructor: 
    // @r, b, g: Lần lượt là đỏ, xanh lá cây và xanh dương. 
    // @a: Màu alpha - thể hiện độ trong suốt. 
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