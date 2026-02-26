#pragma once

#include "../body.hpp"
#include "PhysicsEngine/core/shapes/all_shapes.hpp"
#include "info.hpp"

namespace Collision{
    namespace Resolve{
        void circleCircle(const Shape& circle1, Body& body1, const Shape& circle2, Body& body2, const Info& info);
        void circleRect(const Shape& circle, Body& body1, const Shape& rect, Body& body2, const Info& info);

        void rectCircle(const Shape& rect, Body& body1, const Shape& circle, Body& body2, const Info& info);
        void rectRect(const Shape& rect1, Body& body1, const Shape& rect2, Body& body2, const Info& info);
    }
}