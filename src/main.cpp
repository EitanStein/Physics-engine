#include "PhysicsEngine/core/PhysicsObject.hpp"
#include "PhysicsEngine/logging/log_macros.hpp"

constexpr double timestep = 0.1;

int main(){
    PhysicsObject circle1(5, BodyConfig(Point(0, 10), DirVector(0, 0), DirVector(0, -10)));
    PhysicsObject circle2(5, BodyConfig(Point(0, 10), DirVector(0, 0), DirVector(0, 10)));

    Body& body1 = circle1.getBody();
    Body& body2 = circle2.getBody();
    
    std::cout << "start:\n";
    int repeats = 100;
    for(int i = 0 ; i < repeats ; ++i){
        body1.update(timestep);
        body2.update(timestep);
        if(areOverlapping(circle1, circle2))
        {
            LOG_INFO("step {}: colliding", i);
            LOG_INFO("pre collision resolve values:\n{}, {}\n{}, {}", body1.getVelocity().y, body1.getAcceleration().y, body2.getVelocity().y, body2.getAcceleration().y);
            
            resolveOverlap(circle1, circle2);

            LOG_INFO("new values:\n{}, {}\n{}, {}", body1.getVelocity().y, body1.getAcceleration().y, body2.getVelocity().y, body2.getAcceleration().y);

        }
            
    }
    
    return 0;
}