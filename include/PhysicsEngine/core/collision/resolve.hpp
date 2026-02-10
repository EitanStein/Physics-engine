#pragma once

#include "../body.hpp"
#include "PhysicsEngine/core/shapes/all_shapes.hpp"

namespace Collision{
    namespace Resolve{
        void circleCircle(const Circle& circle1, Body& body1, const Circle& circle2, Body& body2);
    }
}