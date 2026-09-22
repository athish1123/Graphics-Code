#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>
#include <vector>
#include "vec3.h"

using namespace std;

class Framebuffer {
    public:
        Framebuffer() : imageWidth(0), imageHeight(0) {}
        Framebuffer(int w, int h);

        Vec3 lerp(const Vec3& c1,const Vec3& c2, double t);

        void clear(Vec3 c);
        void exportAsPNG(string filename);
        void gradientTB(const Vec3& c1,const Vec3& c2);
        void gradientLR(const Vec3& c1,const Vec3& c2);
        void colorArrayTB(vector<Vec3> cArr);

        void setPixelColor(int width, int height, const Vec3& c);

    private:
        int imageWidth, imageHeight;
        double t;
        vector<Vec3> fbStorage;
        

};

#endif // FRAMEBUFFER_H