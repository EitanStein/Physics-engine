#include "PhysicsEngine/core/collision/dispatch.hpp"
#include "PhysicsEngine/core/collision/detect.hpp"
#include "PhysicsEngine/core/collision/resolve.hpp"
#include <array>


namespace Collision{
    using DetectFunc = bool(*)(const Shape&, const Body&, const Shape&, const Body&, Info&);

    constexpr std::array<std::array<DetectFunc, ShapeT::NUM_SHAPES>, ShapeT::NUM_SHAPES> dispatchTable{
        // circle collisions
        std::array<DetectFunc, ShapeT::NUM_SHAPES>{
            Collision::Detect::circleCircle,
            Collision::Detect::circleRect
        },
        // rectangle collisions
        std::array<DetectFunc, ShapeT::NUM_SHAPES>{
            Collision::Detect::rectCircle,
            Collision::Detect::rectRect
        }
    };

    constexpr DetectFunc getDetectFunc(ShapeT::Type shape1, ShapeT::Type shape2) { 
        return dispatchTable
            [static_cast<size_t>(shape1)]
            [static_cast<size_t>(shape2)];
    }

    bool isColliding(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Info& info){
        if(!Collision::Detect::isBoundingRadiusColliding(shape1, body1, shape2, body2));
            return false;

        return getDetectFunc(shape1.type(), shape2.type())(
            shape1, body1, shape2, body2, info
        );
    }

    
}