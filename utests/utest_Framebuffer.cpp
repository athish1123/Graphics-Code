#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "framebuffer.h"

using namespace std;

Vec3 c1 = Vec3(0.2,0.8,0.4);
Vec3 c2 = Vec3(0.6,0.1,0.5);
Vec3 c3 = Vec3(0.1,0.3,0.7);
Vec3 c4 = Vec3(0.9,0.1,0.5);

TEST_CASE( "Simple Framebuffer Test" )
{
    Framebuffer fb(2560, 1440);
     // fb.clear(fb.lerp(c1, c2, 1));
    // fb.gradientTB(c1 , c2);
    // fb.gradientLR(c1, c2);
    fb.colorArrayTB(vector<Vec3>{c2,c4,c3,c1});
    fb.exportAsPNG("output.png");
}