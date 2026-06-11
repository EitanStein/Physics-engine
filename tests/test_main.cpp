#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include "PhysicsEngine/core/collision/dispatch.hpp"
#include "PhysicsEngine/core/collision/detect.hpp"
#include "PhysicsEngine/core/collision/resolve.hpp"

#include "PhysicsEngine/core/PhysicsObject.hpp"

TEST_CASE("velocity changes are accurate", "[Physics][Movement]"){
    Body test_body(BodyConfig{Point{}, DirVector{5,5}, DirVector{}});
    test_body.update(2);
    REQUIRE(test_body.getPosition() == Point{10,10});
}

TEST_CASE("acceleration changes are accurate", "[Physics][Movement]"){
    Body test_body(BodyConfig{Point{}, DirVector{1,1}, DirVector{2,3}});
    test_body.update(2);
    REQUIRE(test_body.getPosition() == Point{6,8});
    REQUIRE(test_body.getVelocity() == DirVector{5,7});
}

TEST_CASE("Apply force is working", "[Physics][Movement]"){
    Body test_body(BodyConfig{Point{0,5}, DirVector{}, DirVector{0,-10}});
    test_body.update(1);
    REQUIRE(test_body.getPosition() == Point{});

    test_body.applyForce(DirVector{0, 20});
    test_body.update(1);
    REQUIRE(test_body.getPosition() == Point{0, -5});
}


TEST_CASE("Basic collision check", "[Physics][Collision]"){
    BodyConfig config1{};
    BodyConfig config2{};

    Collision::Info info;
    Collision::Info direct_call_info;

    config1.position = Point{0, 5};
    config2.position = Point{5, 5};

    {
        PhysicsObject object1(ShapeFactory::createCircle(3), config1);
        PhysicsObject object2(ShapeFactory::createCircle(5), config2);
        REQUIRE(areOverlapping(object1, object2, info));
        Collision::Detect::circleCircle(object1.getShape(), object1.getBody(),
                                        object2.getShape(), object2.getBody(), direct_call_info);
        REQUIRE(info == direct_call_info);
    }

    {
        PhysicsObject object1(ShapeFactory::createCircle(1), config1);
        PhysicsObject object2(ShapeFactory::createCircle(1), config2);
        REQUIRE(!areOverlapping(object1, object2, info));
    }

    {
        PhysicsObject object1(ShapeFactory::createCircle(3), config1);
        PhysicsObject object2(ShapeFactory::createRect(10, 1), config2);
        REQUIRE(areOverlapping(object1, object2, info));
        Collision::Detect::circleRect(object1.getShape(), object1.getBody(),
                                        object2.getShape(), object2.getBody(), direct_call_info);
        REQUIRE(info == direct_call_info);
    }

    {
        PhysicsObject object1(ShapeFactory::createCircle(3), config1);
        PhysicsObject object2(ShapeFactory::createRect(1, 10), config2);
        REQUIRE(!areOverlapping(object1, object2, info));
    }

    {
        PhysicsObject object1(ShapeFactory::createRect(6, 1), config1);
        PhysicsObject object2(ShapeFactory::createRect(10, 1), config2);
        REQUIRE(areOverlapping(object1, object2, info));
        Collision::Detect::rectRect(object1.getShape(), object1.getBody(),
                                        object2.getShape(), object2.getBody(), direct_call_info);
        REQUIRE(info == direct_call_info);
    }

    {
        PhysicsObject object1(ShapeFactory::createRect(6, 1), config1);
        PhysicsObject object2(ShapeFactory::createRect(1, 10), config2);
        REQUIRE(!areOverlapping(object1, object2, info));
    }

    config1.position = Point{5, 0};
    config2.position = Point{5, 5};

    {
        PhysicsObject object1(ShapeFactory::createCircle(3), config1);
        PhysicsObject object2(ShapeFactory::createRect(10, 1), config2);
        REQUIRE(!areOverlapping(object1, object2, info));
    }

    {
        PhysicsObject object1(ShapeFactory::createRect(1, 10), config1);
        PhysicsObject object2(ShapeFactory::createCircle(3), config2);
        REQUIRE(areOverlapping(object1, object2, info));
        Collision::Detect::rectCircle(object1.getShape(), object1.getBody(),
                                        object2.getShape(), object2.getBody(), direct_call_info);
        REQUIRE(info == direct_call_info);
    }

    {
        PhysicsObject object1(ShapeFactory::createRect(6, 1), config1);
        PhysicsObject object2(ShapeFactory::createRect(10, 1), config2);
        REQUIRE(!areOverlapping(object1, object2, info));
    }

    {
        PhysicsObject object1(ShapeFactory::createRect(6, 1), config1);
        PhysicsObject object2(ShapeFactory::createRect(1, 10), config2);
        REQUIRE(areOverlapping(object1, object2, info));
        Collision::Detect::rectRect(object1.getShape(), object1.getBody(),
                                        object2.getShape(), object2.getBody(), direct_call_info);
        REQUIRE(info == direct_call_info);
    }

    config1.position = Point{0, 0};
    config2.position = Point{5, 5};

    {
        PhysicsObject object1(ShapeFactory::createRect(12, 1), config1);
        PhysicsObject object2(ShapeFactory::createRect(1, 12), config2);
        REQUIRE(areOverlapping(object1, object2, info));
        Collision::Detect::rectRect(object1.getShape(), object1.getBody(),
                                        object2.getShape(), object2.getBody(), direct_call_info);
        REQUIRE(info == direct_call_info);
    }

    {
        PhysicsObject object1(ShapeFactory::createRect(7, 1), config1);
        PhysicsObject object2(ShapeFactory::createRect(1, 7), config2);
        REQUIRE(!areOverlapping(object1, object2, info));
    }

}