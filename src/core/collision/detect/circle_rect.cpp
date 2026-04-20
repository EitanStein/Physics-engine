#include "PhysicsEngine/core/collision/detect.hpp"
#include <cmath>

namespace Collision{
    namespace Detect{
        struct CircleRectCalc {
            Point contact_point;
            DirVector diff;
            double dist_squared;
        };

        inline CircleRectCalc preComputeCircleRect(const Circle& circle, const Point& pos1,
                                           const Rectangle& rect, const Point& pos2)
        {
            CircleRectCalc calc;

            double half_width = rect.getWidth() / 2.0;
            double half_height = rect.getHeight() / 2.0;

            double dx = pos2.x - pos1.x;
            double dy = pos2.y - pos1.y;

            double clamped_x = std::clamp(dx, -half_width, half_width);
            double clamped_y = std::clamp(dy, -half_height, half_height);

            calc.contact_point = Point(pos1.x + clamped_x, pos1.y + clamped_y);
            calc.diff = pos2 - calc.contact_point;

            calc.dist_squared = dotProduct(calc.diff, calc.diff);

            return calc;
        }

        bool circleRect(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2, Info& info){
            const Circle& circle = static_cast<const Circle&>(shape1);
            const Rectangle& rect = static_cast<const Rectangle&>(shape2);
            
            CircleRectCalc calc = preComputeCircleRect(circle, pos1, rect, pos2);

            double radius = circle.getRadius();
            // TODO tangent circles considered overlap or not (currently yes)
            if (calc.dist_squared > radius * radius)
                return false;

            
            double dist = std::sqrt(calc.dist_squared);

            if (dist != 0)
                info.normal = calc.diff / dist;
            else
                info.normal = DirVector(1, 0);

            info.penetration = radius - dist;

            info.contact_point = calc.contact_point;
            
            // TODO deal with circle inside rect situation
            return true;
        }

        bool rectCircle(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2, Info& info){
            bool result = circleRect(shape2, pos2, shape1, pos1, info);
            info.normal *= - 1;
            return result;
        }
    }
}