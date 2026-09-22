// #include "camera.h"

// Camera::Camera(int width, int height)
// {
//     imageWidth = width;
//     imageHeight = height;

//     leftBound = -imageWidth / 2; 
//     rightBound = imageWidth / 2; 
//     topBound = imageHeight / 2;
//     bottomBound = -imageHeight / 2;
// }

// void Camera::generateRay(int &width, int &height, Ray &cRay)
// {
//     U = leftBound + (rightBound - leftBound) * (static_cast<double>(width) + 0.5) / imageWidth;
//     V = bottomBound + (topBound - bottomBound) * (static_cast<double>(height) + 0.5) / imageHeight;

//     Vec3 direction = U * u + V * v - cameraOrigin;
//     cRay = Ray(cameraOrigin, direction);
// }