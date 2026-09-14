#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>
#include <vector>
#include "vec3.h"

using namespace std;

class Framebuffer {
    public:
        Framebuffer() : width(0), height(0) {}
        Framebuffer(int w, int h);
        void clear(Vec3 c);
        void exportAsPNG(string filename);
        Vec3 lerp(const Vec3& c1,const Vec3& c2, double t);
        // void lerp(int x, int y,const  Vec3& c1,const  Vec3& c2, double t);
        void gradientTB(const Vec3& c1,const  Vec3& c2);

    private:
        int width, height;
        double t;
        vector<Vec3> fbStorage;
        

};

#endif // FRAMEBUFFER_H