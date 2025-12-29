#pragma once

#include "point.hpp"

// TODO change class name form body
class Body{
private:
    Point position;
    DirVector velocity;
    DirVector acceleration;

    double mass;
    double restitution;
public:
    Body(Point pos, DirVector starting_v, DirVector starting_a) : position(pos), velocity(starting_v), acceleration(starting_a) { 
        // TODO give non-const values
        mass = 1;
        restitution = 0.8;
    }
    void update(double time_step) {
        // TODO reduce object creations here
        DirVector vel_increase = acceleration * time_step;

        position += (velocity + vel_increase / 2) * time_step;
        velocity += vel_increase;
    }

    void applyForce(const DirVector& direction) {acceleration += direction;}
    void resetSpeed(const DirVector& direction) {velocity = direction;}

    const Point& getPosition() const {return position;}
    const DirVector& getVelocity() const {return velocity;}
    const DirVector& getAcceleration() const {return acceleration;}
    double getMass() const {return mass;}
    double getRestitution() const {return restitution;}
};