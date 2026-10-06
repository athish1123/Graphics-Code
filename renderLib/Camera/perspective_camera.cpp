#define _USE_MATH_DEFINES
#include <cmath>
#include "perspective_camera.h"


PerspectiveCamera::PerspectiveCamera(Vec3 cameraOrigin, Vec3 cameraViewDir, double focalLength, double imagePlaneWidth, int width, int height)
{ 
    imageWidth = width;
    imageHeight = height;

    this->cameraOrigin = cameraOrigin;

    double imagePlaneHeight = imagePlaneWidth * (static_cast<double>(height) / width);

    leftBound = -imagePlaneWidth / 2.0; 
    rightBound = imagePlaneWidth / 2.0; 
    topBound = imagePlaneHeight / 2.0;
    bottomBound = -imagePlaneHeight / 2.0;

    // cameraOrigin = Point3(0, 0, 0);
    // cameraViewDir   = Point3(0, 0, -1);
    // cameraWorldUp  = Vec3(0, 1, 0);

    cameraWorldUp = Vec3(0, 1, 0);

    w = normalize(-cameraViewDir);
    W = focalLength;
    u = normalize(cross(cameraWorldUp, w));
    v = cross(w,u);

    // double fovDegrees = 90.0;
    // double fovRadians = fovDegrees * M_PI / 180.0;
    // W = (imageHeight / 2.0) / tan(fovRadians / 2.0);

    

}

// PerspectiveCamera::PerspectiveCamera(Vec3 origin, Vec3 viewDir, double FocalLength, double imagePlaneWidth, int width, int height)
// {
// }

void PerspectiveCamera::generateRay(int &width, int &height, Ray &cRay)
{
    U = leftBound + (rightBound - leftBound) * (static_cast<double>(width) + 0.5) / imageWidth;
    // V = topBound - (topBound - bottomBound) * (static_cast<double>(height) + 0.5) / imageHeight;
    V = topBound - (topBound - bottomBound) * (static_cast<double>(height) + 0.5) / imageHeight;
    Vec3 direction = U * u + V * v - W * w;
    cRay = Ray(cameraOrigin, direction);
}