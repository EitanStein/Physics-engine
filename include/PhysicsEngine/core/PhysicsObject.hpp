#pragma once

#include "shapes/shape_factory.hpp"
#include "body.hpp"
#include "collision/dispatch.hpp"

class PhysicsObject {
private:
    std::unique_ptr<Shape> shape;
    Body body;
public:
    PhysicsObject(std::unique_ptr<Shape> p_shape, const BodyConfig& body_vars) : shape(std::move(p_shape)), body(body_vars) {}

    Body& getBody() {return body;}
    const Body& getBody() const {return body;}
    
    Shape& getShape() {return *shape;}
    const Shape& getShape() const {return *shape;}
};


inline bool areOverlapping(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2, Collision::Info& info){
    Collision::DetectFunc detect_func = Collision::getDetectFunc(shape1.type(), shape2.type());
    return detect_func(shape1, pos1, shape2, pos2, info);
}

inline bool areOverlapping(const PhysicsObject& obj1, const PhysicsObject& obj2, Collision::Info& info){
    return areOverlapping(obj1.getShape(), obj1.getBody().getPosition(),
                        obj2.getShape(), obj2.getBody().getPosition(), info);
}




inline void resolveOverlap(PhysicsObject& obj1, PhysicsObject& obj2, const Collision::Info& info){
    Collision::Resolve::resolve(obj1.getBody(), obj2.getBody(), info);
}
