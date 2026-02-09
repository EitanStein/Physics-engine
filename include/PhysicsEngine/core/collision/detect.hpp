#pragma once

#include "../body.hpp"
#include "../shape.hpp"

// TODO maybe return collision info instead of just detecting collision and returning bool
namespace Collision{
    namespace Detect{
        bool circleCircle(const Circle& circle1, const Point& pos1, const Circle& circle2, const Point& pos2);
    }
}