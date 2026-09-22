#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "camera.h"

class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera() : imageWidth(0), imageHeight(0) {};
        PerspectiveCamera(int w, int h);

    
    private:
        int imageWidth, imageHeight;
        double leftBound, rightBound, topBound, bottomBound;
        double U, V, W;
        Vec3 u, v, w;
        Point3 cameraOrigin;



};

#endif