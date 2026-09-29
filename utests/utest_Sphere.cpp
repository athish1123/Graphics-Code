#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "Shape/sphere.h"

using Catch::Matchers::WithinAbs;

constexpr double EPS = 1e-9;

TEST_CASE("Ray straight at sphere hits front surface", "[sphere][hit]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;

    REQUIRE(s.intersect(r, 0.001, 100.0, hit));
    REQUIRE_THAT(hit.rayHitParameter, WithinAbs(4.0, EPS));
    REQUIRE_THAT(hit.rayHitPoint.x(), WithinAbs(0.0, EPS));
    REQUIRE_THAT(hit.rayHitPoint.y(), WithinAbs(0.0, EPS));
    REQUIRE_THAT(hit.rayHitPoint.z(), WithinAbs(-4.0, EPS));
}

TEST_CASE("Front hit normal points back toward the ray", "[sphere][normal]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;

    REQUIRE(s.intersect(r, 0.001, 100.0, hit));
    REQUIRE(hit.front_face);
    REQUIRE_THAT(hit.surfaceNormal.x(), WithinAbs(0.0, EPS));
    REQUIRE_THAT(hit.surfaceNormal.y(), WithinAbs(0.0, EPS));
    REQUIRE_THAT(hit.surfaceNormal.z(), WithinAbs(1.0, EPS));
}

TEST_CASE("Off-center hit produces unit-length normal", "[sphere][normal]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.5, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;

    REQUIRE(s.intersect(r, 0.001, 100.0, hit));
    REQUIRE_THAT(hit.surfaceNormal.length_squared(), WithinAbs(1.0, 1e-6));
}

TEST_CASE("Ray passing beside sphere misses", "[sphere][miss]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.0, 5.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;

    REQUIRE_FALSE(s.intersect(r, 0.001, 100.0, hit));
}

TEST_CASE("Sphere behind the ray origin is not hit", "[sphere][miss]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0));
    HitRecord hit;

    REQUIRE_FALSE(s.intersect(r, 0.001, 100.0, hit));
}

TEST_CASE("Tangent ray grazes sphere at one point", "[sphere][edge-case]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(1.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;

    REQUIRE(s.intersect(r, 0.001, 100.0, hit));
    REQUIRE_THAT(hit.rayHitParameter, WithinAbs(5.0, EPS));
}

TEST_CASE("Non-normalized direction gives scaled t but same hit point", "[sphere][hit]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -2.0));
    HitRecord hit;

    REQUIRE(s.intersect(r, 0.001, 100.0, hit));
    REQUIRE_THAT(hit.rayHitParameter, WithinAbs(2.0, EPS));
    REQUIRE_THAT(hit.rayHitPoint.z(), WithinAbs(-4.0, EPS));
}

TEST_CASE("Ray starting inside sphere hits far side with flipped normal", "[sphere][inside]") {
    Sphere s(Point3(0.0, 0.0, 0.0), 1.0);
    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;

    REQUIRE(s.intersect(r, 0.001, 100.0, hit));
    REQUIRE_THAT(hit.rayHitParameter, WithinAbs(1.0, EPS));
    REQUIRE_THAT(hit.rayHitPoint.z(), WithinAbs(-1.0, EPS));
    REQUIRE_FALSE(hit.front_face);
    REQUIRE_THAT(hit.surfaceNormal.z(), WithinAbs(1.0, EPS));
}

TEST_CASE("t_max before first root rejects hit", "[sphere][range]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;

    REQUIRE_FALSE(s.intersect(r, 0.001, 3.0, hit));
}

TEST_CASE("t_min past near root falls back to far root", "[sphere][range]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;

    REQUIRE(s.intersect(r, 4.5, 100.0, hit));
    REQUIRE_THAT(hit.rayHitParameter, WithinAbs(6.0, EPS));
}

TEST_CASE("Both roots outside range rejects hit", "[sphere][range]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;

    REQUIRE_FALSE(s.intersect(r, 7.0, 100.0, hit));
}

TEST_CASE("Failed intersect leaves HitRecord untouched", "[sphere][immutability]") {
    Sphere s(Point3(0.0, 0.0, -5.0), 1.0);
    Ray r(Point3(0.0, 5.0, 0.0), Vec3(0.0, 0.0, -1.0));
    HitRecord hit;
    hit.rayHitParameter = 42.0;

    REQUIRE_FALSE(s.intersect(r, 0.001, 100.0, hit));
    REQUIRE_THAT(hit.rayHitParameter, WithinAbs(42.0, EPS));
}

TEST_CASE("Sphere off-origin with larger radius hits correctly", "[sphere][hit]") {
    Sphere s(Point3(10.0, 0.0, 0.0), 3.0);
    Ray r(Point3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0));
    HitRecord hit;

    REQUIRE(s.intersect(r, 0.001, 100.0, hit));
    REQUIRE_THAT(hit.rayHitParameter, WithinAbs(7.0, EPS));
    REQUIRE_THAT(hit.rayHitPoint.x(), WithinAbs(7.0, EPS));
}