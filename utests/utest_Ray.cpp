#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "ray.h"
 
using Catch::Matchers::WithinAbs;
 
constexpr double EPS = 1e-9;
 
TEST_CASE("Ray construction stores origin and direction", "[ray][construction]") {
    Point3 origin(1.0, 2.0, 3.0);
    Vec3 direction(4.0, 5.0, 6.0);
    Ray r(origin, direction);
 
    REQUIRE_THAT(r.getOrigin().x(), WithinAbs(1.0, EPS));
    REQUIRE_THAT(r.getOrigin().y(), WithinAbs(2.0, EPS));
    REQUIRE_THAT(r.getOrigin().z(), WithinAbs(3.0, EPS));
 
    REQUIRE_THAT(r.getDirection().x(), WithinAbs(4.0, EPS));
    REQUIRE_THAT(r.getDirection().y(), WithinAbs(5.0, EPS));
    REQUIRE_THAT(r.getDirection().z(), WithinAbs(6.0, EPS));
}
 
TEST_CASE("Default-constructed ray has zero origin and direction", "[ray][construction]") {
    Ray r;
    REQUIRE_THAT(r.getOrigin().x(), WithinAbs(0.0, EPS));
    REQUIRE_THAT(r.getOrigin().y(), WithinAbs(0.0, EPS));
    REQUIRE_THAT(r.getOrigin().z(), WithinAbs(0.0, EPS));
    REQUIRE_THAT(r.getDirection().x(), WithinAbs(0.0, EPS));
    REQUIRE_THAT(r.getDirection().y(), WithinAbs(0.0, EPS));
    REQUIRE_THAT(r.getDirection().z(), WithinAbs(0.0, EPS));
}
 
TEST_CASE("rayAt(0) returns the origin", "[ray][evaluation]") {
    Point3 origin(1.0, 1.0, 1.0);
    Vec3 direction(2.0, 0.0, 0.0);
    Ray r(origin, direction);
 
    Point3 p = r.rayAt(0.0);
    REQUIRE_THAT(p.x(), WithinAbs(1.0, EPS));
    REQUIRE_THAT(p.y(), WithinAbs(1.0, EPS));
    REQUIRE_THAT(p.z(), WithinAbs(1.0, EPS));
}
 
TEST_CASE("rayAt(1) returns origin plus direction", "[ray][evaluation]") {
    Point3 origin(0.0, 0.0, 0.0);
    Vec3 direction(3.0, -2.0, 1.5);
    Ray r(origin, direction);
 
    Point3 p = r.rayAt(1.0);
    REQUIRE_THAT(p.x(), WithinAbs(3.0, EPS));
    REQUIRE_THAT(p.y(), WithinAbs(-2.0, EPS));
    REQUIRE_THAT(p.z(), WithinAbs(1.5, EPS));
}
 
TEST_CASE("rayAt with arbitrary positive t scales direction correctly", "[ray][evaluation]") {
    Point3 origin(1.0, 2.0, 3.0);
    Vec3 direction(2.0, 4.0, -2.0);
    Ray r(origin, direction);
 
    double t = 2.5;
    Point3 p = r.rayAt(t);
    REQUIRE_THAT(p.x(), WithinAbs(1.0 + t * 2.0, EPS));
    REQUIRE_THAT(p.y(), WithinAbs(2.0 + t * 4.0, EPS));
    REQUIRE_THAT(p.z(), WithinAbs(3.0 + t * -2.0, EPS));
}
 
TEST_CASE("rayAt with arbitrary negative t moves backward along direction", "[ray][evaluation]") {
    Point3 origin(0.0, 0.0, 0.0);
    Vec3 direction(1.0, 1.0, 1.0);
    Ray r(origin, direction);
 
    double t = -3.0;
    Point3 p = r.rayAt(t);
    REQUIRE_THAT(p.x(), WithinAbs(-3.0, EPS));
    REQUIRE_THAT(p.y(), WithinAbs(-3.0, EPS));
    REQUIRE_THAT(p.z(), WithinAbs(-3.0, EPS));
}
 
TEST_CASE("rayAt is linear: evaluating at t1 then extrapolating matches direct evaluation", "[ray][evaluation]") {
    Point3 origin(5.0, -1.0, 2.0);
    Vec3 direction(1.0, 2.0, 3.0);
    Ray r(origin, direction);
 
    // p(t1 + t2) should equal p(t1) + t2 * direction
    double t1 = 1.7;
    double t2 = 0.8;
    Point3 combined = r.rayAt(t1 + t2);
    Point3 stepwise = r.rayAt(t1) + t2 * r.getDirection();
 
    REQUIRE_THAT(combined.x(), WithinAbs(stepwise.x(), EPS));
    REQUIRE_THAT(combined.y(), WithinAbs(stepwise.y(), EPS));
    REQUIRE_THAT(combined.z(), WithinAbs(stepwise.z(), EPS));
}
 
TEST_CASE("Ray origin and direction are not mutated by rayAt calls", "[ray][immutability]") {
    Point3 origin(1.0, 2.0, 3.0);
    Vec3 direction(4.0, 5.0, 6.0);
    Ray r(origin, direction);
 
    // Call rayAt several times with different t values
    r.rayAt(0.0);
    r.rayAt(1.0);
    r.rayAt(-5.0);
    r.rayAt(100.0);
 
    REQUIRE_THAT(r.getOrigin().x(), WithinAbs(1.0, EPS));
    REQUIRE_THAT(r.getOrigin().y(), WithinAbs(2.0, EPS));
    REQUIRE_THAT(r.getOrigin().z(), WithinAbs(3.0, EPS));
 
    REQUIRE_THAT(r.getDirection().x(), WithinAbs(4.0, EPS));
    REQUIRE_THAT(r.getDirection().y(), WithinAbs(5.0, EPS));
    REQUIRE_THAT(r.getDirection().z(), WithinAbs(6.0, EPS));
}
 
TEST_CASE("Two rays constructed from the same values are independent", "[ray][immutability]") {
    Point3 origin(1.0, 1.0, 1.0);
    Vec3 direction(2.0, 2.0, 2.0);
 
    Ray r1(origin, direction);
    Ray r2(origin, direction);
 
    r1.rayAt(10.0);
    r2.rayAt(-10.0);
 
    // Mutating the local variables afterward shouldn't affect already-constructed rays
    origin = Point3(999.0, 999.0, 999.0);
    direction = Vec3(999.0, 999.0, 999.0);
 
    REQUIRE_THAT(r1.getOrigin().x(), WithinAbs(1.0, EPS));
    REQUIRE_THAT(r2.getOrigin().x(), WithinAbs(1.0, EPS));
    REQUIRE_THAT(r1.getDirection().x(), WithinAbs(2.0, EPS));
    REQUIRE_THAT(r2.getDirection().x(), WithinAbs(2.0, EPS));
}
 
TEST_CASE("rayAt handles small floating-point t within tolerance", "[ray][numerical]") {
    Point3 origin(0.1, 0.2, 0.3);
    Vec3 direction(1e-8, 1e-8, 1e-8);
    Ray r(origin, direction);
 
    double t = 1e6; // large t against tiny direction, should stay numerically sane
    Point3 p = r.rayAt(t);
 
    REQUIRE_THAT(p.x(), WithinAbs(0.1 + t * 1e-8, 1e-6));
    REQUIRE_THAT(p.y(), WithinAbs(0.2 + t * 1e-8, 1e-6));
    REQUIRE_THAT(p.z(), WithinAbs(0.3 + t * 1e-8, 1e-6));
}
 
TEST_CASE("rayAt accumulates floating-point error within acceptable bounds", "[ray][numerical]") {
    Point3 origin(0.0, 0.0, 0.0);
    Vec3 direction(0.1, 0.1, 0.1);
    Ray r(origin, direction);
 
    // Sum of many small steps should match a single large step within tolerance
    double accumulatedT = 0.0;
    Point3 last = r.getOrigin();
    for (int i = 0; i < 10; ++i) {
        accumulatedT += 0.1;
    }
    Point3 direct = r.rayAt(accumulatedT);
    Point3 expected = r.rayAt(1.0);
 
    REQUIRE_THAT(direct.x(), WithinAbs(expected.x(), 1e-9));
    REQUIRE_THAT(direct.y(), WithinAbs(expected.y(), 1e-9));
    REQUIRE_THAT(direct.z(), WithinAbs(expected.z(), 1e-9));
}
 
TEST_CASE("rayAt with zero direction always returns the origin", "[ray][numerical][edge-case]") {
    Point3 origin(3.0, -4.0, 5.0);
    Vec3 direction(0.0, 0.0, 0.0);
    Ray r(origin, direction);
 
    for (double t : {-1000.0, -1.0, 0.0, 1.0, 1000.0}) {
        Point3 p = r.rayAt(t);
        REQUIRE_THAT(p.x(), WithinAbs(3.0, EPS));
        REQUIRE_THAT(p.y(), WithinAbs(-4.0, EPS));
        REQUIRE_THAT(p.z(), WithinAbs(5.0, EPS));
    }
}