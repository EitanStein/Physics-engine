#pragma once

#include "point.hpp"

const double DEFAULT_MASS = 1;
const double DEFAULT_RESTITUTION = 0.8;

// TODO change class name from body
class Body{
private:
    Point position;
    DirVector velocity;
    DirVector acceleration;

    double mass;
    double restitution;
public:
    Body(Point pos, DirVector starting_vel, DirVector starting_acc, double mass=DEFAULT_MASS, double restitution=DEFAULT_RESTITUTION) 
        : position(pos), velocity(starting_vel), acceleration(starting_acc), mass(mass), restitution(restitution) { 
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


double calcRestitutionCoefficient(const Body& body1, const Body& body2){
    return (body1.getRestitution()/2 + body2.getRestitution()/2);
}