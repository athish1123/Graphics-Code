#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera{
    public:
        virtual ~Camera() = default;

        virtual void generateRay(int width, int height, Ray& cRay) = 0;
        virtual void generateRay(int width, int height, Ray& cRay, double offsetX, double offsetY) = 0;
    
    protected:
        Vec3 u, v, w;
        Point3 cameraOrigin, cameraWorldUp;
        int imageWidth = 0, imageHeight = 0;
        double leftBound = 0.0, rightBound = 0.0, topBound = 0.0, bottomBound = 0.0;
        double W = 0.0;
};



#endif