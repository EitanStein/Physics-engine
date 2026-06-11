#pragma once

#include "point.hpp"
#include "PhysicsEngine/logging/log_macros.hpp"

const double DEFAULT_MASS = 1;
const double DEFAULT_RESTITUTION = 0.8;


struct BodyConfig{
    Point position{};
    DirVector velocity{};
    DirVector acceleration{};

    double angle = 0;
    double angular_vel = 0;
    double inertia = 0;
    double inverse_inertia = 0;

    double mass = DEFAULT_MASS;
    double restitution = DEFAULT_RESTITUTION;
};


class Body{
private:
    Point position{};
    DirVector velocity{};
    DirVector acceleration{};

    double mass{};
    double restitution{};

    double angle = 0;
    double angular_vel = 0;
    double inertia = 0;
    double inverse_inertia = 0;
public:
    Body(const BodyConfig& body_vars) 
        : position(body_vars.position), velocity(body_vars.velocity), acceleration(body_vars.acceleration),
         mass(body_vars.mass), restitution(body_vars.restitution), 
         angle(body_vars.angle), angular_vel(body_vars.angular_vel) { 
        resetInertia(body_vars.inertia);
    }
    void update(double time_step) {
        // TODO reduce object creations here
        DirVector vel_increase = acceleration * time_step;

        position += (velocity + vel_increase / 2) * time_step;
        velocity += vel_increase;

        // TODO add angular vel decay?
        angle += angular_vel * time_step;
    }

    void applyForce(const DirVector& direction) {acceleration += direction;}
    void resetSpeed(const DirVector& direction) {velocity = direction;}
    void resetAngularSpeed(double angular_spd) {angular_vel = angular_spd;}
    void resetInertia(double inertia) {
        inertia = inertia; 
        inverse_inertia = (inertia == 0) ? 0 : 1/inertia;
    }
    void movePos(const DirVector& distance) {position += distance;}

    constexpr const Point& getPosition() const {return position;}
    constexpr const DirVector& getVelocity() const {return velocity;}
    constexpr const DirVector& getAcceleration() const {return acceleration;}
    constexpr double getMass() const {return mass;}
    constexpr double getInverseMass() const {
        // TODO different handle of 0 mass objects
        if(mass == 0){
            LOG_ERROR("Can't calculate inverse mass of 0 mass");
            return 1/0.001;
        }
        // TODO handle immovale objects (return 0)

        return 1/mass;
    } 
    constexpr double getRestitution() const {return restitution;}

    constexpr double getAngle() const {return angle;}
    constexpr double getAngularVel() const {return angular_vel;}
    constexpr double getInertia() const {return inertia;}
    constexpr double getInverseInertia() const {return inverse_inertia;}
};


inline constexpr double calcRestitutionCoefficient(const Body& body1, const Body& body2){
    return (body1.getRestitution()/2 + body2.getRestitution()/2);
}