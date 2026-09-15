#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
 
#include "vec3.h"
 
#include <cmath>
#include <cstdio>
#include <string>
 
bool nearly_equal(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}
 
TEST_CASE("Vec3 constructors and accessors", "[vec3]") {
    Vec3 default_vec;
    REQUIRE(nearly_equal(default_vec.x(), 0.0));
    REQUIRE(nearly_equal(default_vec.y(), 0.0));
    REQUIRE(nearly_equal(default_vec.z(), 0.0));
 
    Vec3 v(1.0, 2.0, 3.0);
    REQUIRE(nearly_equal(v.x(), 1.0));
    REQUIRE(nearly_equal(v.y(), 2.0));
    REQUIRE(nearly_equal(v.z(), 3.0));
}
 
TEST_CASE("Vec3 index operator", "[vec3]") {
    Vec3 v(4.0, 5.0, 6.0);
 
    REQUIRE(nearly_equal(v[0], 4.0));
    REQUIRE(nearly_equal(v[1], 5.0));
    REQUIRE(nearly_equal(v[2], 6.0));
 
    v[1] = 99.0;
    REQUIRE(nearly_equal(v[1], 99.0));
    REQUIRE(nearly_equal(v.y(), 99.0));
}
 
TEST_CASE("Vec3 arithmetic operators", "[vec3]") {
    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(4.0, 5.0, 6.0);
    double scale_amount = 2.0;
 
    Vec3 sum = a + b;
    REQUIRE(nearly_equal(sum.x(), 5.0));
    REQUIRE(nearly_equal(sum.y(), 7.0));
    REQUIRE(nearly_equal(sum.z(), 9.0));
 
    Vec3 diff = b - a;
    REQUIRE(nearly_equal(diff.x(), 3.0));
    REQUIRE(nearly_equal(diff.y(), 3.0));
    REQUIRE(nearly_equal(diff.z(), 3.0));
 
    Vec3 prod = a * b;
    REQUIRE(nearly_equal(prod.x(), 4.0));
    REQUIRE(nearly_equal(prod.y(), 10.0));
    REQUIRE(nearly_equal(prod.z(), 18.0));
 
    Vec3 scaled = a * scale_amount;
    REQUIRE(nearly_equal(scaled.x(), 2.0));
    REQUIRE(nearly_equal(scaled.y(), 4.0));
    REQUIRE(nearly_equal(scaled.z(), 6.0));
 
    Vec3 scaled_reversed = scale_amount * a;
    REQUIRE(nearly_equal(scaled_reversed.x(), 2.0));
    REQUIRE(nearly_equal(scaled_reversed.y(), 4.0));
    REQUIRE(nearly_equal(scaled_reversed.z(), 6.0));
 
    Vec3 divided = scaled / scale_amount;
    REQUIRE(nearly_equal(divided.x(), a.x()));
    REQUIRE(nearly_equal(divided.y(), a.y()));
    REQUIRE(nearly_equal(divided.z(), a.z()));
}
 
TEST_CASE("Vec3 compound assignment and negation", "[vec3]") {
    Vec3 v(1.0, 2.0, 3.0);
 
    Vec3 added = v + Vec3(1.0, 1.0, 1.0);
    REQUIRE(nearly_equal(added.x(), 2.0));
    REQUIRE(nearly_equal(added.y(), 3.0));
    REQUIRE(nearly_equal(added.z(), 4.0));
 
    Vec3 multiplied = v * 2.0;
    REQUIRE(nearly_equal(multiplied.x(), 2.0));
    REQUIRE(nearly_equal(multiplied.y(), 4.0));
    REQUIRE(nearly_equal(multiplied.z(), 6.0));
 
    Vec3 divided = multiplied / 2.0;
    REQUIRE(nearly_equal(divided.x(), 1.0));
    REQUIRE(nearly_equal(divided.y(), 2.0));
    REQUIRE(nearly_equal(divided.z(), 3.0));
 
    Vec3 negated = -v;
    REQUIRE(nearly_equal(negated.x(), -1.0));
    REQUIRE(nearly_equal(negated.y(), -2.0));
    REQUIRE(nearly_equal(negated.z(), -3.0));
}
 
TEST_CASE("Vec3 dot, cross, length, normalize", "[vec3]") {
    Vec3 a(1.0, 0.0, 0.0);
    Vec3 b(0.0, 1.0, 0.0);
 
    double dot_result = dot(a, b);
    REQUIRE(nearly_equal(dot_result, 0.0));
 
    Vec3 cross_result = cross(a, b);
    REQUIRE(nearly_equal(cross_result.x(), 0.0));
    REQUIRE(nearly_equal(cross_result.y(), 0.0));
    REQUIRE(nearly_equal(cross_result.z(), 1.0));
 
    Vec3 c(3.0, 4.0, 0.0);
    REQUIRE(nearly_equal(c.length_squared(), 25.0));
    REQUIRE(nearly_equal(c.length(), 5.0));
 
    Vec3 normalized = normalize(c);
    REQUIRE(nearly_equal(normalized.length(), 1.0));
    REQUIRE(nearly_equal(normalized.x(), 0.6));
    REQUIRE(nearly_equal(normalized.y(), 0.8));
}