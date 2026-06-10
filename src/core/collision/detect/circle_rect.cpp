#include "PhysicsEngine/core/collision/detect.hpp"
#include <cmath>

namespace Collision{
    namespace Detect{
        struct CircleRectCalc {
            Point closet_rect_contact;
            DirVector rotated_center_diff;
            DirVector diff_to_closet_contact;
            double dist_squared_to_closet_contact;
        };

        inline CircleRectCalc preComputeCircleRect(const Point& circle_pos, const Point& rect_pos,
                                                    double rect_half_width, double rect_half_height, double rect_angle)
        {
            CircleRectCalc calc;

            calc.rotated_center_diff = rotate(rect_pos - circle_pos, -rect_angle);

            calc.closet_rect_contact = {std::clamp(calc.rotated_center_diff.x, -rect_half_width, rect_half_width),
                                        std::clamp(calc.rotated_center_diff.y, -rect_half_height, rect_half_height)};

            calc.diff_to_closet_contact = calc.closet_rect_contact - calc.rotated_center_diff;
            calc.dist_squared_to_closet_contact = dotProduct(calc.diff_to_closet_contact, calc.diff_to_closet_contact);

            return calc;
        }

        bool circleRect(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Info& info){
            double circle_rad = static_cast<const Circle&>(shape1).getRadius();
            double rect_half_width = static_cast<const Rectangle&>(shape2).getHalfWidth();
            double rect_half_height = static_cast<const Rectangle&>(shape2).getHalfHeight();

            const Point& circle_pos = body1.getPosition();
            const Point& rect_pos = body2.getPosition();
            
            CircleRectCalc calc = preComputeCircleRect(circle_pos, rect_pos, rect_half_width, rect_half_height, body2.getAngle());
            
            if(calc.dist_squared_to_closet_contact >= circle_rad*circle_rad)
                return false;

            double dist_to_closest_contact = std::sqrt(calc.dist_squared_to_closet_contact);

            DirVector rotated_normal;

            // TODO how plausible is this scenario?
            if (dist_to_closest_contact == 0.0f) [[unlikely]]
            {
                float dx = rect_half_width - std::abs(calc.rotated_center_diff.x);
                float dy = rect_half_height - std::abs(calc.rotated_center_diff.y);

                if (dx < dy)
                    rotated_normal = { (calc.rotated_center_diff.x > 0) ? -1.0f : 1.0f, 0 };
                else
                    rotated_normal = { 0, (calc.rotated_center_diff.y > 0) ? -1.0f : 1.0f };

                info.penetration = std::min(dx, dy);
            }
            else
            {
                rotated_normal = calc.diff_to_closet_contact * (1.0f / dist_to_closest_contact);
                info.penetration = circle_rad - dist_to_closest_contact;
            }

            info.normal = rotate(rotated_normal, body2.getAngle());

            if (dotProduct(rect_pos - circle_pos, info.normal) < 0)
                info.normal = info.normal * -1.0f;

            info.contact_point = rect_pos - rotate(calc.closet_rect_contact, body2.getAngle());

            return true;
        }

        bool rectCircle(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Info& info){
            bool result = circleRect(shape2, body2, shape1, body1, info);
            info.normal *= - 1;
            return result;
        }
    }
}