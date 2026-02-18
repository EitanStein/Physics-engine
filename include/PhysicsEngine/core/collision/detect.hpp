#pragma once

#include "../body.hpp"
#include "PhysicsEngine/core/shapes/all_shapes.hpp"

// TODO maybe return collision info instead of just detecting collision and returning bool
// collision info could include 'is colliding', 'collision point', 'collision normal' and more
namespace Collision{
    namespace Detect{
        bool circleCircle(const Shape& circle1, const Point& pos1, const Shape& circle2, const Point& pos2);
    }
}