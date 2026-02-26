#include "PhysicsEngine/core/collision/detect.hpp"
#include <cmath>

namespace Collision{
    namespace Detect{
        // circle collisions
        bool circleCircle(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2, Info& info){
            const Circle& circle1 = static_cast<const Circle&>(shape1);
            const Circle& circle2 = static_cast<const Circle&>(shape2);

            double origin_dist = dist(pos1, pos2);
            // TODO tangent circles considered overlap or not
            if(origin_dist <= circle1.getRadius() + circle2.getRadius())
                return true;
            
            return false;
        }

        bool circleRect(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2, Info& info){
            const Circle& circle = static_cast<const Circle&>(shape1);
            const Rectangle& rect = static_cast<const Rectangle&>(shape2);

            // TODO tangect considered overlap?
            if((std::abs(pos1.x-pos2.x) <= circle.getRadius() + rect.getWidth()/2) && 
                (std::abs(pos1.y-pos2.y) <= circle.getRadius() + rect.getHeight()/2))
            {
                return true;
            }
                
            return false;
        }

        // rectangle collisions
        bool rectCircle(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2, Info& info){
            return circleRect(shape2, pos2, shape1, pos1, info);
        }

        bool rectRect(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2, Info& info){
            const Rectangle& rect1 = static_cast<const Rectangle&>(shape1);
            const Rectangle& rect2 = static_cast<const Rectangle&>(shape2);

            // TODO tangect considered overlap?
            if((2*std::abs(pos1.x-pos2.x) <= rect1.getWidth() + rect2.getWidth()) && 
                (2*std::abs(pos1.y-pos2.y) <= rect1.getHeight() + rect2.getHeight()))
            {
                return true;
            }

            return false;
        }
    }
}