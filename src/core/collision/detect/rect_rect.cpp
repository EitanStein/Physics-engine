#include "PhysicsEngine/core/collision/detect.hpp"
#include <array>
#include <cmath>


namespace Collision{
    namespace Detect{
        struct rectRectCalc {
            Point collision_point;
            DirVector diff;
        };

        inline double calcOverlap(const DirVector& axis, const std::array<DirVector, 4>& axes,
                                    const Rectangle& rect1,  const Rectangle& rect2, const DirVector& diff){
            
            double half_width1 = rect1.getWidth() / 2.0;
            double half_height1 = rect1.getHeight() / 2.0;
            double half_width2 = rect2.getWidth() / 2.0;
            double half_height2 = rect2.getHeight() / 2.0;

            double projection1 =
                half_width1 * std::abs(dotProduct(axis, axes[0])) +
                half_height1 * std::abs(dotProduct(axis, axes[1]));

            double projection2 =
                half_width2 * std::abs(dotProduct(axis, axes[2])) +
                half_height2 * std::abs(dotProduct(axis, axes[3]));

            double dist = std::abs(dotProduct(diff, axis));

            return projection1 + projection2 - dist;
        }


        bool rectRect(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Info& info){
            const Rectangle& rect1 = static_cast<const Rectangle&>(shape1);
            const Rectangle& rect2 = static_cast<const Rectangle&>(shape2);

            const Point& pos1 = body1.getPosition();
            const Point& pos2 = body2.getPosition();

            std::array<DirVector, 4> axes;

            axes[0] = rotate({1, 0}, body1.getAngle());
            axes[1] = rotate({0, 1}, body1.getAngle());
            axes[2] = rotate({1, 0}, body2.getAngle());
            axes[3] = rotate({0, 1}, body2.getAngle());

            double min_overlap = std::numeric_limits<float>::max();
            DirVector smallest_axis;

            DirVector center_diff = pos2 - pos1;

            for (int i = 0; i < 4; i++)
            {
                DirVector axis = normalize(axes[i]);

                double overlap = calcOverlap(axis, axes, rect1, rect2, center_diff);

                if (overlap <= 0.0f)
                    return false;

                if (overlap < min_overlap)
                { 
                    min_overlap = overlap;
                    smallest_axis = axis;
                }
            }

            
            if (dotProduct(center_diff, smallest_axis) < 0)
                smallest_axis = smallest_axis * -1.0f;

            info.normal = smallest_axis;
            info.penetration = min_overlap;

            Point contact = pos1;

            DirVector local_normal = {
                dotProduct(info.normal, axes[0]),
                dotProduct(info.normal, axes[1])
            };

            info.contact_point = pos1 +
                                axes[0] * (local_normal.x > 0 ? rect1.getWidth() : -rect1.getWidth()) / 2 +
                                axes[1] * (local_normal.y > 0 ? rect1.getHeight() : -rect1.getHeight()) / 2;

            return true;
        }
    }
}