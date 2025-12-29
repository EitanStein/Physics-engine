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
    void resetSpeed(const DirVector& direction) { body->resetSpeed(direction); }

    bool contains(const Point& point) const{
        return shape->contains(body->getPosition(), point);
    }

    const Point& getPos() const { return body->getPosition(); }
    // TODO handle in circle Physics class
    double getRadius() const { return static_cast<Circle*>(shape.get())->getRadius();}

    void update(double time_step){
        // TODO handle collisions
        body->update(time_step);
    }
};


// TODO return collision info instead of bool
// TODO potantially change to 'willCollide in upcoming time step'
bool areCirclesOverlapping(const PhysicsObject& obj1, const PhysicsObject& obj2){
    double origin_dist = dist(obj1.getPos(), obj2.getPos());
    // TODO tangent circles considered overlap or not
    if(origin_dist <= obj1.getRadius() + obj2.getRadius())
        return true;
    
    return false;
}
