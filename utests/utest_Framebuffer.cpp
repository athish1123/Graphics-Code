#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "framebuffer.h"

TEST_CASE( "Simple Framebuffer Test" )
{
    Framebuffer fb(2560, 1440);
    // fb.lerp(Vec3(0.2,0.8,0.4), Vec3(0.6,0.1,0.5), 1);
    fb.transitionColor(Vec3(0.2,0.8,0.4), Vec3(0.6,0.1,0.5));
    // fb.clear(Vec3(0.5, 0.8, 1));
    fb.exportAsPNG("output.png");
}