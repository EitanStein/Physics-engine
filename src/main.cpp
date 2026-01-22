#include "PhysicsEngine/core/PhysicsObject.hpp"
#include "PhysicsEngine/logging/log_macros.h"

constexpr double timestep = 0.1;

int main(){
    PhysicsObject circle1(5, Point(0, 10));
    PhysicsObject circle2(5, Point(0, -10));
    circle2.applyForce(DirVector(0,20));
    
    std::cout << "start:\n";
    int repeats = 100;
    for(int i = 0 ; i < repeats ; ++i){
        circle1.update(timestep);
        circle2.update(timestep);
        if(areCirclesOverlapping(circle1, circle2))
        {
            LOG_INFO("step {}: colliding", i);
            LOG_INFO("pre collision resolve values:\n{}, {}\n{}, {}", circle1.getVelocity().y, circle1.getAcceleration().y, circle2.getVelocity().y, circle2.getAcceleration().y);
            
            resolveCirclesOverlap(circle1, circle2);

            LOG_INFO("new values:\n{}, {}\n{}, {}", circle1.getVelocity().y, circle1.getAcceleration().y, circle2.getVelocity().y, circle2.getAcceleration().y);

        }
            
    }
    
    return 0;
}