#include "perspective_camera.h"

PerspectiveCamera::PerspectiveCamera(int width, int height)
{
    imageWidth = width;
    imageHeight = height;

    leftBound = -imageWidth / 2; 
    rightBound = imageWidth / 2; 
    topBound = imageHeight / 2;
    bottomBound = -imageHeight / 2;
}

void PerspectiveCamera::generateRay(int &width, int &height, Ray &cRay)
{
    u_coord = leftBound + (rightBound - leftBound) * (static_cast<double>(width) + 0.5) / imageWidth;
    V = bottomBound + (topBound - bottomBound) * (static_cast<double>(height) + 0.5) / imageHeight;

    Vec3 direction = u_coord * u + V * v - cameraOrigin;
    cRay = Ray(cameraOrigin, direction);
}