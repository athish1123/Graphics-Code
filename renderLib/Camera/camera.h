#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera{
    public:
        virtual void generateRay(int& width, int& height, Ray& cRay) = 0;
    
    protected:
        Vec3 u, v, w;
        Point3 cameraOrigin, cameraWorldUp;
        int imageWidth, imageHeight;
        double leftBound, rightBound, topBound, bottomBound;
        double U, V, W;
};



#endif