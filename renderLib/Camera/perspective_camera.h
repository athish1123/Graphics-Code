#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "camera.h"

class PerspectiveCamera : public Camera {
    public:
        // PerspectiveCamera() : imageWidth(0), imageHeight(0) {};
        PerspectiveCamera(Vec3 cameraOrigin, Vec3 cameraViewDir, double focalLength, double imagePlaneWidth, int width, int height);

        void generateRay(int& width, int& height, Ray& cRay) override;
};

#endif