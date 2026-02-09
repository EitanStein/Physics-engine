#include "PhysicsEngine/core/collision/detect.hpp"

namespace Collision{
    namespace Detect{
        bool circleCircle(const Circle& circle1, const Point& pos1, const Circle& circle2, const Point& pos2){
            double origin_dist = dist(pos1, pos2);
            // TODO tangent circles considered overlap or not
            if(origin_dist <= circle1.getRadius() + circle2.getRadius())
                return true;
            
            return false;
        }
    }
}