#pragma once

#include "shapes/shape_factory.hpp"
#include "body.hpp"
#include "collision/dispatch.hpp"

class PhysicsObject {
private:
    std::unique_ptr<Shape> shape;
    Body body;

    void initInertia(){
        switch(shape->type()){
            case ShapeT::Type::Circle:{
                double radius = static_cast<Circle*>(shape.get())->getRadius();
                body.resetInertia(0.5 * body.getMass() * radius * radius);
                break;
            }
            case ShapeT::Type::Rectangle: {
                double width = static_cast<Rectangle*>(shape.get())->getWidth();
                double height = static_cast<Rectangle*>(shape.get())->getHeight();
                body.resetInertia(0.5 * body.getMass() * (width * width + height * height));
                break;
            }
            default:{
                body.resetInertia(0);
            }
        }
    }
public:
    PhysicsObject(std::unique_ptr<Shape> p_shape, const BodyConfig& body_vars) : shape(std::move(p_shape)), body(body_vars) {
        initInertia();
    }

    Body& getBody() {return body;}
    const Body& getBody() const {return body;}
    
    Shape& getShape() {return *shape;}
    const Shape& getShape() const {return *shape;}
};


inline bool areOverlapping(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Collision::Info& info){
    Collision::DetectFunc detect_func = Collision::getDetectFunc(shape1.type(), shape2.type());
    return detect_func(shape1, body1, shape2, body2, info);
}

inline bool areOverlapping(const PhysicsObject& obj1, const PhysicsObject& obj2, Collision::Info& info){
    return areOverlapping(obj1.getShape(), obj1.getBody(),
                        obj2.getShape(), obj2.getBody(), info);
}




inline void resolveOverlap(PhysicsObject& obj1, PhysicsObject& obj2, const Collision::Info& info){
    Collision::Resolve::resolve(obj1.getBody(), obj2.getBody(), info);
}
