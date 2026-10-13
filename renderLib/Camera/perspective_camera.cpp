#include <cmath>

#include "perspective_camera.h"
#include "vec3.h"

#include <stdexcept>

PerspectiveCamera::PerspectiveCamera(Vec3 cameraOrigin, Vec3 cameraViewDir, double focalLength, double imagePlaneWidth, int width, int height)
{
    if (width <= 0 || height <= 0 || !(focalLength > 0.0) || !(imagePlaneWidth > 0.0)) {
        throw std::invalid_argument("Camera dimensions, focal length, and image plane width must be positive");
    }
    if (cameraViewDir.length_squared() == 0.0) {
        throw std::invalid_argument("Camera view direction must be non-zero");
    }

    imageWidth = width;
    imageHeight = height;

    this->cameraOrigin = cameraOrigin;

    double imagePlaneHeight = imagePlaneWidth * (static_cast<double>(height) / width);

    leftBound = -imagePlaneWidth / 2.0;
    rightBound = imagePlaneWidth / 2.0;
    topBound = imagePlaneHeight / 2.0;
    bottomBound = -imagePlaneHeight / 2.0;

    cameraWorldUp = Vec3(0, 1, 0);

    w = normalize(-cameraViewDir);
    W = focalLength;
    Vec3 right = cross(cameraWorldUp, w);
    if (right.length_squared() < 1e-12) {
        cameraWorldUp = Vec3(0, 0, 1);
        right = cross(cameraWorldUp, w);
    }
    u = normalize(right);
    v = cross(w,u);

    topLeftRayDirection = leftBound * u + topBound * v - W * w;
    pixelDeltaX = ((rightBound - leftBound) / imageWidth) * u;
    pixelDeltaY = -((topBound - bottomBound) / imageHeight) * v;
}

void PerspectiveCamera::generateRay(int width, int height, Ray& cRay)
{
    generateRay(width, height, cRay, 0.0, 0.0);
}

void PerspectiveCamera::generateRay(int width, int height, Ray &cRay, double offsetX, double offsetY)
{
    const Vec3 direction = topLeftRayDirection
        + (static_cast<double>(width) + offsetX) * pixelDeltaX
        + (static_cast<double>(height) + offsetY) * pixelDeltaY;
    cRay = Ray(cameraOrigin, direction);
}