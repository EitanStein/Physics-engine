#include "PhysicsEngine/core/collision/detect.hpp"
#include <cmath>

namespace Collision{
    namespace Detect{
        bool circleCircle(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Info& info){
            int radius1 = static_cast<const Circle&>(shape1).getRadius();
            int radius2 = static_cast<const Circle&>(shape2).getRadius();

            const Point& pos1 = body1.getPosition();
            const Point& pos2 = body2.getPosition();

            DirVector center_diff = pos2 - pos1;
            double center_dist = dist(pos1, pos2);


            info.normal = (center_dist != 0) ? center_diff / center_dist : DirVector{1, 0};
            info.penetration = radius1 + radius2 - center_dist;

            Point contact_1 = pos1 + info.normal * radius1;
            Point contact_2 = pos2 - info.normal * radius2;

            info.contact_point = (contact_1 + contact_2) / 2;

            return true;
        }
    }
}