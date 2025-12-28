#pragma once

#include "shape.hpp"
#include "body.hpp"
#include <memory>

class PhysicsObject {
private:
    std::unique_ptr<Shape> shape;
    std::unique_ptr<Body> body;
public:
    // TODO handle creation of different shapes (factory?)
    // TODO handle starting vel, accelerate
    PhysicsObject(double radius, Point pos) {
        shape = std::make_unique<Circle>(radius);
        body = std::make_unique<Body>(pos, DirVector(), DirVector(0, -10));
    }

    void applyForce(const DirVector& direction) { body->applyForce(direction); }

    bool contains(const Point& point) const{
        return shape->contains(body->getPosition(), point);
    }

    const Point& getPos() const { return body->getPosition(); }

    void update(double time_step){
        // TODO handle collisions
        body->update(time_step);
    }
};