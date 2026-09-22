#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera{
    public:
        // Camera() : imageWidth(0), imageHeight(0) {}
        // Camera(int width, int height);
        
        // X and Y are the areas your looping thorugh aka where you are in your array and then you put your cRay there
        virtual void generateRay(int& width, int& height, Ray& cRay) = 0;
    
    protected:
        // int imageWidth, imageHeight;
        // double leftBound, rightBound, topBound, bottomBound;
        // double U, V, W;
        Vec3 u, v, w;
        Point3 cameraWorldUp;

    private:

};



#endif