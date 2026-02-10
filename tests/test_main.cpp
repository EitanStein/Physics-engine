#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "PhysicsEngine/core/PhysicsObject.hpp"

TEST_CASE("velocity changes are accurate", "[Physics][Movement]"){
    Body test_body(BodyConfig(Point(0,0), DirVector(5,5), DirVector(0,0)));
    test_body.update(2);
    REQUIRE(test_body.getPosition() == Point(10,10));
}

TEST_CASE("acceleration changes are accurate", "[Physics][Movement]"){
    Body test_body(BodyConfig(Point(0,0), DirVector(1,1), DirVector(2,3)));
    test_body.update(2);
    REQUIRE(test_body.getPosition() == Point(6,8));
    REQUIRE(test_body.getVelocity() == DirVector(5,7));
}

TEST_CASE("Apply force is working", "[Physics][Movement]"){
    Body test_body(BodyConfig(Point(0,5), DirVector(0,0), DirVector(0,-10)));
    test_body.update(1);
    REQUIRE(test_body.getPosition() == Point(0, 0));

    test_body.applyForce(DirVector(0, 20));
    test_body.update(1);
    REQUIRE(test_body.getPosition() == Point(0, -5));
}


TEST_CASE("Basic collision check", "[Physics][Collision]"){
    BodyConfig config;
    config.position = Point(0, 5);
    PhysicsObject object1(std::move(ShapeFactory::createCircle(3)), config);
    config.position = Point(5, 5);
    PhysicsObject object2(std::move(ShapeFactory::createCircle(5)), config);
    REQUIRE(areOverlapping(object1, object2));

    config.position = Point(0, 5);
    PhysicsObject object3(std::move(ShapeFactory::createCircle(1)), config);
    config.position = Point(5, 5);
    PhysicsObject object4(std::move(ShapeFactory::createCircle(1)), config);
    REQUIRE(!areOverlapping(object3, object4));
}