#pragma once

#include "../body.hpp"
#include "../shape.hpp"

namespace Collision{
    namespace Resolve{
        void circleCircle(const Circle& circle1, Body& body1, const Circle& circle2, Body& body2);
    }
}