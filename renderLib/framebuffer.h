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
        void lerp(int x, int y, Vec3 c1, Vec3 c2, double t);
        void transitionColor(Vec3 c1, Vec3 c2, double t);

    private:
        int width, height;
        vector<Vec3> fbStorage;
        

};

#endif // FRAMEBUFFER_H