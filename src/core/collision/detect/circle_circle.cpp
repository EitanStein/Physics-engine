#include "PhysicsEngine/core/collision/detect.hpp"
#include <cmath>

namespace Collision{
    namespace Detect{
        struct CircleCircleCalc {
            DirVector diff;
            double dist_squared;
        };

        inline CircleCircleCalc preComputeCircleCircle(const Point& pos1, const Point& pos2)
        {
            CircleCircleCalc calc;
            calc.diff = pos2 - pos1;
            calc.dist_squared = dotProduct(calc.diff, calc.diff);
            return calc;
        }

        bool circleCircle(const Shape& shape1, const Point& pos1, const Shape& shape2, const Point& pos2, Info& info){
            const Circle& circle1 = static_cast<const Circle&>(shape1);
            const Circle& circle2 = static_cast<const Circle&>(shape2);
            
            CircleCircleCalc calc = preComputeCircleCircle(pos1, pos2);

            double radius_sum = circle1.getRadius() + circle2.getRadius();
            // TODO tangent circles considered overlap or not (currently yes)
            if (calc.dist_squared > radius_sum * radius_sum)
                return false;

            double dist = std::sqrt(calc.dist_squared);

            if (dist != 0)
                info.normal = calc.diff / dist;
            else
                info.normal = DirVector(1, 0);

            info.penetration = radius_sum - dist;

            return true;
        }
    }
}