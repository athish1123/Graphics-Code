#include <iostream>
#include "vec3.h"
#include "framebuffer.h"
#include "Camera/perspective_camera.h"

using namespace std;

Vec3 c1 = Vec3(0.2,0.8,0.4);
Vec3 c2 = Vec3(0.6,0.1,0.5);
Vec3 c3 = Vec3(0.1,0.3,0.7);
Vec3 c4 = Vec3(0.9,0.1,0.5);

int main()
{
    // Framebuffer fb(2560, 1440);
    // // fb.clear(fb.lerp(c1, c2, 1));
    // // fb.gradientTB(c1 , c2);
    // // fb.gradientLR(c1, c2);
    // fb.colorArrayTB(vector<Vec3>{c1,c4,c3,c1});
    // fb.exportAsPNG("output1.png");



    Framebuffer fb(200,200);
    PerspectiveCamera p(Vec3(0,0,0), Vec3(5,6,2), 1.3, 2.0, fb.getImageWidth(), fb.getImageHeight());
    // PerspectiveCamera(Vec3 cameraOrigin, Vec3 cameraViewDir, double focalLength, double imagePlaneWidth, int width, int height);


    for (int x=0; x<200; ++x) 
    {
        for (int y=0; y<200; ++y) 
        {
            Ray r;
            p.generateRay( x, y, r );
            // convert ray direction to a color here
            Vec3 dir = r.getDirection();
            dir = normalize(dir);                          // now components are in [-1, 1]
            Vec3 ray_dir_color = (dir + Vec3(1,1,1)) * 0.5; // remap to [0, 1]
            fb.setPixelColor(x, y, ray_dir_color);
        }
    }
    cout << "works";
    fb.exportAsPNG( "defaultCamRayColors.png" );

}