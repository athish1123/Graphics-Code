#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"

#include <iostream>

class Color : public Vec3
{
public:

    // uses vec3 default constructor
    using Vec3::Vec3;

    void write_color(std::ostream &out, const Color &pixel_color) {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();

        // Translate the [0,1] component values to the byte range [0,255].
        int rbyte = int(255.999 * r);
        int gbyte = int(255.999 * g);
        int bbyte = int(255.999 * b);

        // Write out the pixel color components.
        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    }


    static Color fromVec3(Vec3 vec) {
        return Color(vec.x(), vec.y(), vec.z());
    }

    // i love static funcs
    static Color red()         { return Color(1.0, 0.0, 0.0); }
    static Color maroon()      { return Color(0.5, 0.0, 0.0); }
    static Color coral()       { return Color(1.0, 0.5, 0.31); }
    static Color salmon()      { return Color(0.98, 0.5, 0.45); }
    static Color orange()      { return Color(1.0, 0.5, 0.0); }
    static Color peach()       { return Color(1.0, 0.8, 0.64); }
    static Color tan()         { return Color(0.82, 0.71, 0.55); }
    static Color yellow()      { return Color(1.0, 1.0, 0.0); }
    static Color lime()        { return Color(0.5, 1.0, 0.5); }
    static Color green()       { return Color(0.0, 0.5, 0.0); }
    static Color forestGreen() { return Color(0.05, 0.3, 0.05); }
    static Color mint()        { return Color(0.3, .8, .65); }
    static Color cyan()        { return Color(0.0, 1.0, 1.0); }
    static Color skyBlue()     { return Color(0.53, 0.81, 0.98); }
    static Color blue()        { return Color(0.0, 0.0, 1.0); }
    static Color indigo()      { return Color(0.29, 0.0, 0.51); }
    static Color lavender()    { return Color(0.75, 0.5, 0.85); }
    static Color purple()      { return Color(0.5, 0.0, 0.5); }
    static Color magenta()     { return Color(1.0, 0.0, 1.0); }
    static Color pink()        { return Color(1.0, 0.5, 0.75); }
    static Color brown()       { return Color(0.4, 0.26, 0.13); }
    static Color white()       { return Color(1.0, 1.0, 1.0); }
    static Color black()       { return Color(0.0, 0.0, 0.0); }
    static Color grey()        { return Color(0.5, 0.5, 0.5); }
    static Color darkGrey()    { return Color(0.25, 0.25, 0.25); }
    static Color lightGrey()   { return Color(0.75, 0.75, 0.75); }
};


#endif