#include "vec3.h"
#include "framebuffer.h"
#include "png++/png.hpp"
#include "color.h"
#include <iostream>



Framebuffer::Framebuffer(int width, int height)
{
    imageWidth = width;
    imageHeight = height;
    fbStorage.resize(imageWidth * imageHeight);
}


void Framebuffer::clear(Vec3 c)
{
    for(int index = 0; index < fbStorage.size(); index++)
    {
        fbStorage[index] = c;
    }
}

Vec3 Framebuffer::lerp(const Vec3& c1, const Vec3& c2, double t)
{
    Vec3 c = (1-t) * c1 + t * c2;
    return c;
}


void Framebuffer::gradientTB(const Vec3& c1,const  Vec3& c2)
{
    for (size_t y = 0; y < imageHeight; ++y)
        {
            t = static_cast<double>(y)/imageHeight;
            for (size_t x = 0; x < imageWidth; ++x)
            {
                Vec3 c = (1-t) * c1 + t * c2;
                fbStorage[y * imageWidth + x] = lerp(c1, c2, t);
            }
        }
}

void Framebuffer::gradientLR(const Vec3& c1,const  Vec3& c2)
{
    for (size_t y = 0; y < imageHeight; ++y)
        {
            for (size_t x = 0; x < imageWidth; ++x)
            {
                t = static_cast<double>(x)/imageWidth;
                fbStorage[y * imageWidth + x] = lerp(c1, c2, t);
            }
        }
}


void Framebuffer::colorArrayTB(vector<Vec3> cArr)
{
    int h = imageHeight/cArr.size();
    for(size_t z = 0; z < cArr.size(); ++z)
    {
        Vec3 c = cArr[z];
        for(size_t y = z * h; y < (z+1) * h; ++y)
        {
            for (size_t x = 0; x < imageWidth; ++x)
            {
                fbStorage[y * imageWidth + x] = c;
            }
        }   
    }
}

void Framebuffer::setPixelColor(int width, int height, const Vec3 &c)
{
    fbStorage[height * imageWidth + width] = c;
}


void Framebuffer::exportAsPNG(string filename)
{
    png::image< png::rgb_pixel > imData( imageWidth, imageHeight );
        for (size_t y = 0; y < imData.get_height(); ++y)
        {
            for (size_t x = 0; x < imData.get_width(); ++x)
            {
                imData[y][x] = png::rgb_pixel(
                    int(255.999 * fbStorage[y * imageWidth + x].x()),
                    int(255.999 * fbStorage[y * imageWidth + x].y()),
                    int(255.999 * fbStorage[y * imageWidth + x].z())
                );
            }
        }
        imData.write( filename );
}