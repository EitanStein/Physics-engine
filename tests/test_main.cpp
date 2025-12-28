#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "PhysicsEngine/core/PhysicsObject.hpp"

TEST_CASE("velocity changes are accurate", "Physics"){
    Body test_body(Point(0,0), DirVector(5,5), DirVector(0,0));
    test_body.update(2);
    REQUIRE(test_body.getPosition() == Point(10,10));
}

TEST_CASE("acceleration changes are accurate", "Physics"){
    Body test_body(Point(0,0), DirVector(1,1), DirVector(2,3));
    test_body.update(2);
    REQUIRE(test_body.getPosition() == Point(6,8));
    REQUIRE(test_body.getVelocity() == DirVector(5,7));
}

TEST_CASE("Apply force is working", "Physics"){
    PhysicsObject object(3, Point(0, 5));
    object.update(1);
    REQUIRE(object.getPos() == Point(0, 0));

    object.applyForce(DirVector(0, 20));
    object.update(1);
    REQUIRE(object.getPos() == Point(0, -5));
}