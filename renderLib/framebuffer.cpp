#include "vec3.h"
#include "framebuffer.h"
#include "png++/png.hpp"
#include "color.h"
#include <iostream>
Framebuffer::Framebuffer(int w, int h)
{
    width = w;
    height = h;
    fbStorage.resize(width * height);
}

void Framebuffer::clear(Vec3 c)
{
    for(int index = 0; index < fbStorage.size(); index++)
    {
        fbStorage[index] = c;
    }
}

void Framebuffer::lerpColor(const Vec3& c1, const Vec3& c2, double t)
{
    for(int index = 0; index < fbStorage.size(); index++)
    {
        Vec3 c = (1-t) * c1 + t * c2;
        fbStorage[index] = c;
    }
}

// void Framebuffer::lerp(int x, int y, const Vec3& c1, const Vec3& c2, double t)
// {
//     Vec3 c = (1-t) * c1 + t * c2;
//     fbStorage[y * width + x] = c;
// }

void Framebuffer::transitionColor(const Vec3& c1,const  Vec3& c2)
{
    for (size_t y = 0; y < height; ++y)
        {
            t = static_cast<double>(y)/height;
            for (size_t x = 0; x < width; ++x)
            {
                Vec3 c = (1-t) * c1 + t * c2;
                fbStorage[y * width + x] = c = c;
            }
        }
}

void Framebuffer::exportAsPNG(string filename)
{
    png::image< png::rgb_pixel > imData( width, height );
        for (size_t y = 0; y < imData.get_height(); ++y)
        {
            for (size_t x = 0; x < imData.get_width(); ++x)
            {
                imData[y][x] = png::rgb_pixel(
                    int(255.999 * fbStorage[y * width + x].x()),
                    int(255.999 * fbStorage[y * width + x].y()),
                    int(255.999 * fbStorage[y * width + x].z())
                );
            }
        }
        imData.write( filename );
}