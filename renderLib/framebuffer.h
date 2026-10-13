#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <string>
#include <vector>

#include "vec3.h"

class Framebuffer {
    public:
        Framebuffer();
        Framebuffer(int imageWidth, int imageHeight);

        Vec3 lerp(const Vec3& c1, const Vec3& c2, double t);

        void clear(Vec3 c);
        void exportAsPNG(std::string filename);
        void gradientTB(const Vec3& c1, const Vec3& c2);
        void gradientLR(const Vec3& c1, const Vec3& c2);
        void colorArrayTB(std::vector<Vec3> cArr);

        void setPixelColor(int width, int height, const Vec3& c);

        int getImageWidth() const;
        int getImageHeight() const;

    private:
        int imageWidth, imageHeight;
        std::vector<Vec3> fbStorage;

};

#endif // FRAMEBUFFER_H