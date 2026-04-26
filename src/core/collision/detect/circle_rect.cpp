#include "PhysicsEngine/core/collision/detect.hpp"
#include <cmath>

namespace Collision{
    namespace Detect{
        struct CircleRectCalc {
            Point closet_local_contact;
            DirVector localized_diff;
            DirVector diff;
            double dist_squared;
        };

        inline CircleRectCalc preComputeCircleRect(const Circle& circle, const Point& circle_pos,
                                           const Rectangle& rect, const Point& rect_pos, double rect_angle)
        {
            CircleRectCalc calc;

            double half_width = rect.getWidth() / 2.0;
            double half_height = rect.getHeight() / 2.0;

            DirVector center_diff = rect_pos - circle_pos;
            calc.localized_diff = rotate(center_diff, -rect_angle);

            calc.closet_local_contact = {std::clamp(calc.localized_diff.x, -half_width, half_width),
                                        std::clamp(calc.localized_diff.y, -half_height, half_height)};

            calc.diff = calc.closet_local_contact - calc.localized_diff;
            calc.dist_squared = dotProduct(calc.diff, calc.diff);

            return calc;
        }

        bool circleRect(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Info& info){
            const Circle& circle = static_cast<const Circle&>(shape1);
            const Rectangle& rect = static_cast<const Rectangle&>(shape2);

            const Point& circle_pos = body1.getPosition();
            const Point& rect_pos = body2.getPosition();
            
            CircleRectCalc calc = preComputeCircleRect(circle, circle_pos, rect, rect_pos, body2.getAngle());

            double radius = circle.getRadius();
            // TODO tangent circles considered overlap or not (currently yes)
            if (calc.dist_squared > radius * radius)
                return false;

            
            double dist = std::sqrt(calc.dist_squared);

            DirVector normal_local;

            if (dist == 0.0f)
            {
                float dx = rect.getWidth()/2 - std::abs(calc.localized_diff.x);
                float dy = rect.getHeight()/2 - std::abs(calc.localized_diff.y);

                if (dx < dy)
                    normal_local = { (calc.localized_diff.x > 0) ? -1.0f : 1.0f, 0 };
                else
                    normal_local = { 0, (calc.localized_diff.y > 0) ? -1.0f : 1.0f };

                info.penetration = std::min(dx, dy);
            }
            else
            {
                normal_local = calc.diff * (1.0f / dist);
                info.penetration = radius - dist;
            }

            info.normal = rotate(normal_local, body2.getAngle());

            if (dotProduct(rect_pos - circle_pos, info.normal) < 0)
                info.normal = info.normal * -1.0f;

            info.contact_point = rect_pos - rotate(calc.closet_local_contact, body2.getAngle());

            return true;
        }

        bool rectCircle(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Info& info){
            bool result = circleRect(shape2, body2, shape1, body1, info);
            info.normal *= - 1;
            return result;
        }
    }
}