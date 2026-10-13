#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "camera.h"

class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(Vec3 cameraOrigin, Vec3 cameraViewDir, double focalLength, double imagePlaneWidth, int width, int height);

        void generateRay(int width, int height, Ray& cRay) override;
        void generateRay(int width, int height, Ray& cRay, double offsetX, double offsetY) override;

    private:
        Vec3 topLeftRayDirection;
        Vec3 pixelDeltaX;
        Vec3 pixelDeltaY;
};

#endif