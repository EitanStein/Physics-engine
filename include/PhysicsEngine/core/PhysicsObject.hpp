#pragma once

#include "shape.hpp"
#include "body.hpp"
#include "collision/detect.hpp"
#include "collision/resolve.hpp"
#include "PhysicsEngine/logging/log_macros.hpp"
#include <memory>
#include <iostream>

class PhysicsObject {
private:
    std::unique_ptr<Shape> shape;
    Body body;
public:
    // TODO handle creation of different shapes (factory?)
    PhysicsObject(double radius, const BodyConfig& body_vars) : body(body_vars) {
        shape = std::make_unique<Circle>(radius);
    }

    Body& getBody() {return body;}
    const Body& getBody() const {return body;}
    
    Shape& getShape() {return *shape;}
    const Shape& getShape() const {return *shape;}
};


inline bool areOverlapping(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2){
    return Collision::Detect::circleCircle(static_cast<const Circle&>(shape1), pos1, 
                                            static_cast<const Circle&>(shape2), pos2);
}

inline bool areOverlapping(const PhysicsObject& obj1, const PhysicsObject& obj2){
    return areOverlapping(obj1.getShape(), obj1.getBody().getPosition(),
                            obj2.getShape(), obj2.getBody().getPosition());
}




inline void resolveOverlap(PhysicsObject& obj1, PhysicsObject& obj2){
    Collision::Resolve::circleCircle(static_cast<const Circle&>(obj1.getShape()), obj1.getBody(),
                                    static_cast<const Circle&>(obj2.getShape()), obj2.getBody());
}
