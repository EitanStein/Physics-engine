#include "PhysicsEngine/core/PhysicsObject.hpp"
#include <iostream>

constexpr double timestep = 0.1;

int main(){
    PhysicsObject object(5, Point());
    Point origin;
    
    int repeats = 100;
    for(int i = 0 ; i < repeats ; ++i){
        object.update(timestep);
        if(object.contains(origin))
            std::cout << "touching origin\n";
    }
    
    return 0;
}