#include "PhysicsEngine/core/collision/detect.hpp"

namespace Collision{
    namespace Detect{
        // circle collisions
        bool circleCircle(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2){
            const Circle& circle1 = static_cast<const Circle&>(shape1);
            const Circle& circle2 = static_cast<const Circle&>(shape2);

            double origin_dist = dist(pos1, pos2);
            // TODO tangent circles considered overlap or not
            if(origin_dist <= circle1.getRadius() + circle2.getRadius())
                return true;
            
            return false;
        }

        bool circleRect(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2){
            // TODO
            return false;
        }

        // rectangle collisions
        bool rectCircle(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2){
            return circleRect(shape2, pos2, shape1, pos1);
        }

        bool rectRect(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2){
            // TODO
            return false;
        }
    }
}