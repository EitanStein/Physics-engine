#pragma once

#include "point.hpp"

// TODO change class name form body
class Body{
private:
    Point position;
    DirVector velocity;
    DirVector acceleration;
public:
    Body(Point pos, DirVector starting_v, DirVector starting_a) : position(pos), velocity(starting_v), acceleration(starting_a) {}
    void update(double time_step) {
        // TODO reduce object creations here
        DirVector vel_increase = acceleration * time_step;

        position += (velocity + vel_increase / 2) * time_step;
        velocity += vel_increase;
    }
    const Point& getPosition() const {return position;}
    const DirVector& getVelocity() const {return velocity;}
    const DirVector& getAcceleration() const {return acceleration;}
};