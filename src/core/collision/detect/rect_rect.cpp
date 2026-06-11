#include "PhysicsEngine/core/collision/detect.hpp"
#include <array>
#include <cmath>
#include <utility>


namespace Collision{
    namespace Detect{
        inline double calcOverlap(const DirVector& axis, const std::array<DirVector, 4>& axes,
                                    const Rectangle& rect1,  const Rectangle& rect2, const DirVector& diff){

            double rect1_projection =
                rect1.getHalfWidth() * std::abs(dotProduct(axis, axes[0])) +
                rect1.getHalfHeight() * std::abs(dotProduct(axis, axes[1]));

            double rect2_projection =
                rect2.getHalfWidth() * std::abs(dotProduct(axis, axes[2])) +
                rect2.getHalfHeight() * std::abs(dotProduct(axis, axes[3]));

            double dist = std::abs(dotProduct(diff, axis));

            return rect1_projection + rect2_projection - dist;
        }

        inline std::pair<DirVector, double> calcMinOverlapAxis(const std::array<DirVector, 4>& axes, 
                                                            const Rectangle& rect1, const Rectangle& rect2,
                                                            Point pos1, Point pos2)
        {
            double min_overlap = std::numeric_limits<float>::max();
            DirVector smallest_axis;

            DirVector center_diff = pos2 - pos1;

            for (int i = 0; i < 4; i++)
            {
                DirVector axis = axes[i];

                double overlap = calcOverlap(axis, axes, rect1, rect2, center_diff);

                if (overlap <= 0.0f)
                    return std::make_pair(DirVector{}, 0);

                if (overlap < min_overlap)
                { 
                    min_overlap = overlap;
                    smallest_axis = axis;
                }
            }

            if (dotProduct(center_diff, smallest_axis) < 0)
                smallest_axis = smallest_axis * -1.0f;
            
            return std::make_pair(smallest_axis, min_overlap);
        }


        bool rectRect(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Info& info){
            const Rectangle& rect1 = static_cast<const Rectangle&>(shape1);
            const Rectangle& rect2 = static_cast<const Rectangle&>(shape2);

            const Point& pos1 = body1.getPosition();
            const Point& pos2 = body2.getPosition();

            std::array<DirVector, 4> axes{
                rotate({1, 0}, body1.getAngle()),
                rotate({0, 1}, body1.getAngle()),
                rotate({1, 0}, body2.getAngle()),
                rotate({0, 1}, body2.getAngle())
            };

            std::tie(info.normal, info.penetration) = calcMinOverlapAxis(axes, rect1, rect2, pos1, pos2);

            if(info.penetration == 0.0f)
                return false;

            DirVector rotated_normal{
                dotProduct(info.normal, axes[0]),
                dotProduct(info.normal, axes[1])
            };

            info.contact_point = pos1 +
                                axes[0] * (rotated_normal.x > 0 ? rect1.getHalfWidth() : -rect1.getHalfWidth()) +
                                axes[1] * (rotated_normal.y > 0 ? rect1.getHalfHeight() : -rect1.getHalfHeight());

            return true;
        }
    }
}