#pragma once

#include "../body.hpp"
#include "PhysicsEngine/core/shapes/all_shapes.hpp"
#include "info.hpp"

// TODO maybe return collision info instead of just detecting collision and returning bool
// collision info could include 'is colliding', 'collision point', 'collision normal' and more
namespace Collision{
    namespace Detect{
        bool circleCircle(const Shape& circle1, const Point& pos1, const Shape& circle2, const Point& pos2, Info& info);
        bool circleRect(const Shape& circle, const Point& pos1, const Shape& rect, const Point& pos2, Info& info);

        bool rectCircle(const Shape& rect, const Point& pos1, const Shape& circle, const Point& pos2, Info& info);
        bool rectRect(const Shape& rect1, const Point& pos1, const Shape& rect2, const Point& pos2, Info& info);
    }
}