#include "PhysicsEngine/core/collision/dispatch.hpp"
#include "PhysicsEngine/core/collision/detect.hpp"
#include "PhysicsEngine/core/collision/resolve.hpp"
#include <array>


namespace Collision{
    std::array<std::array<DetectFunc, ShapeT::NUM_SHAPES>, ShapeT::NUM_SHAPES> dispatchTable{
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


    DetectFunc getDetectFunc(ShapeT::Type shape1, ShapeT::Type shape2) { 
        return dispatchTable
            [static_cast<size_t>(shape1)]
            [static_cast<size_t>(shape2)];
    }
}