#pragma once

#include "point.hpp"

const double DEFAULT_MASS = 1;
const double DEFAULT_RESTITUTION = 0.8;


struct BodyConfig{
    Point position = Point(0,0);
    DirVector velocity = DirVector(0,0);
    DirVector acceleration = DirVector(0,0);

    double mass = DEFAULT_MASS;
    double restitution = DEFAULT_RESTITUTION;

    BodyConfig() {}
    BodyConfig(Point position, DirVector velocity, DirVector acceleration, double mass=DEFAULT_MASS, double restitution=DEFAULT_RESTITUTION) :
        position(position), velocity(velocity), acceleration(acceleration), mass(mass), restitution(restitution) {}

    BodyConfig(const BodyConfig& other) = default;

    BodyConfig(BodyConfig&& other) = default;
};


class Body{
private:
    Point position;
    DirVector velocity;
    DirVector acceleration;

    double mass;
    double restitution;
public:
    Body(const BodyConfig& body_vars) 
        : position(body_vars.position), velocity(body_vars.velocity), acceleration(body_vars.acceleration),
         mass(body_vars.mass), restitution(body_vars.restitution) { 
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