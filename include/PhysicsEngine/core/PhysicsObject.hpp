#pragma once

#include "shape.hpp"
#include "body.hpp"
#include <memory>
#include <iostream>

class PhysicsObject {
private:
    std::unique_ptr<Shape> shape;
    Body body;
public:
    // TODO handle creation of different shapes (factory?)
    // TODO handle starting vel, accelerate
    PhysicsObject(double radius, Point pos) : body(pos, DirVector(), DirVector(0, -10)) {
        shape = std::make_unique<Circle>(radius);
    }

    Body& getBody() {return body;}
    const Body& getBody() const {return body;}
    Shape* getShape() const {return shape.get();}
};


// TODO return collision info instead of bool
// TODO potantially change to 'willCollide in upcoming time step'
bool areCirclesOverlapping(const PhysicsObject& obj1, const PhysicsObject& obj2){
    const Body& body1 = obj1.getBody();
    Circle* circle1 = static_cast<Circle*>(obj1.getShape());
    
    const Body& body2 = obj2.getBody();
    Circle* circle2 = static_cast<Circle*>(obj2.getShape());

    double origin_dist = dist(body1.getPosition(), body2.getPosition());
    // TODO tangent circles considered overlap or not
    if(origin_dist <= circle1->getRadius() + circle2->getRadius())
        return true;
    
    return false;
}

// TODO change to a more general function? uses body info only atm and no shape/circle related data
DirVector calcCircleCollisionNormal(const PhysicsObject& obj1, const PhysicsObject& obj2){
    DirVector diff = obj2.getBody().getPosition() - obj1.getBody().getPosition();
    return diff/dist(diff, Point(0,0));
}

void resolveCirclesOverlap(PhysicsObject& obj1, PhysicsObject& obj2){
    Body& body1 = obj1.getBody();
    Body& body2 = obj2.getBody();

    // calculate speed impulse change
    double restitution_coeff = std::min(body1.getRestitution(), body2.getRestitution());
    DirVector relative_velocity = body2.getVelocity() - body1.getVelocity();
    DirVector normal = calcCircleCollisionNormal(obj1, obj2);

    double normal_of_rel_velocity = dotProduct(relative_velocity, normal);

    if(normal_of_rel_velocity >= 0){
        // TODO logging
        std::cout << "In collision resolution but normalized rel velocity sugests they do not collide\n";
        return;
    }

    double impulse = -(1 + restitution_coeff) * normal_of_rel_velocity / (1/body1.getMass() + 1/body2.getMass());

    body1.resetSpeed(body1.getVelocity() - normal*(impulse/body1.getMass()));
    body2.resetSpeed(body2.getVelocity() + normal*(impulse/body2.getMass()));
}
