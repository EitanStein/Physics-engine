#pragma once

#include "shape.hpp"
#include "body.hpp"
#include <memory>
#include <iostream>

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
    double getRestitution() const { return body->getRestitution();}
    double getMass() const { return body->getMass();}

    // TODO handle in circle Physics class
    double getRadius() const { return static_cast<Circle*>(shape.get())->getRadius();}


    const DirVector& getVelocity() const {return body->getVelocity();}
    const DirVector& getAcceleration() const { return body->getAcceleration();}
    


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


DirVector calcCircleCollisionNormal(const PhysicsObject& obj1, const PhysicsObject& obj2){
    // TODO handles only circles now need to be able to handle other collisions later
    DirVector diff = obj2.getPos() - obj1.getPos();
    return diff/dist(diff, Point(0,0));
}

void resolveCirclesOverlap(PhysicsObject& obj1, PhysicsObject& obj2){

    // calculate speed impulse change
    double restitution_coeff = std::min(obj1.getRestitution(), obj2.getRestitution());
    DirVector relative_velocity = obj2.getVelocity() - obj1.getVelocity();
    DirVector normal = calcCircleCollisionNormal(obj1, obj2);

    double normal_of_rel_velocity = dotProduct(relative_velocity, normal);

    if(normal_of_rel_velocity >= 0){
        // TODO logging
        std::cout << "In collision resolution but normalized rel velocity sugests they do not collide\n";
        return;
    }

    double impulse = -(1 + restitution_coeff) * normal_of_rel_velocity / (1/obj1.getMass() + 1/obj2.getMass());

    obj1.resetSpeed(obj1.getVelocity() - normal*(impulse/obj1.getMass()));
    obj2.resetSpeed(obj2.getVelocity() + normal*(impulse/obj2.getMass()));


    // calculate acceleration change
    DirVector temp_acc = obj1.getAcceleration();
    obj1.applyForce(obj2.getAcceleration());
    obj2.applyForce(temp_acc);
}
