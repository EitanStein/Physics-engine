#include "PhysicsEngine/core/collision/dispatch.hpp"
#include "PhysicsEngine/core/collision/detect.hpp"
#include "PhysicsEngine/core/collision/resolve.hpp"
#include <array>


namespace Collision{
    std::array<std::array<std::pair<DetectFunc, ResolveFunc>, ShapeT::NUM_SHAPES>, ShapeT::NUM_SHAPES> dispatchTable{
        // circle collisions
        std::array<std::pair<DetectFunc, ResolveFunc>, ShapeT::NUM_SHAPES>{
            std::pair<DetectFunc, ResolveFunc>{Collision::Detect::circleCircle, Collision::Resolve::circleCircle}
        }
    };


    DetectFunc getDetectFunc(ShapeT::Type shape1, ShapeT::Type shape2) { 
        return dispatchTable
            [static_cast<size_t>(shape1)]
            [static_cast<size_t>(shape2)].first;
    }

    ResolveFunc getResolveFunc(ShapeT::Type shape1, ShapeT::Type shape2) { 
        return dispatchTable
            [static_cast<size_t>(shape1)]
            [static_cast<size_t>(shape2)].second;
    }
}