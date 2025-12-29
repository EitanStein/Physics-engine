#include "PhysicsEngine/core/PhysicsObject.hpp"
#include <iostream>

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
            std::cout << "step " << i << ": colliding\n";
            std::cout << "pre collision resolve values:\n" << circle1.getVelocity().y << ", " << circle1.getAcceleration().y << '\n' << 
                            circle2.getVelocity().y << ", " << circle2.getAcceleration().y << '\n';

            resolveCirclesOverlap(circle1, circle2);
            std::cout << "new values:\n" << circle1.getVelocity().y << ", " << circle1.getAcceleration().y << '\n' << 
                            circle2.getVelocity().y << ", " << circle2.getAcceleration().y << '\n';
        }
            
    }
    
    return 0;
}