#include "PhysicsEngine/core/collision/detect.hpp"
#include <cmath>


namespace Collision{
    namespace Detect{
        struct rectRectCalc {
            Point collision_point;
            DirVector diff;
        };

        inline rectRectCalc preComputeRectRect(const Rectangle& rect1, const Point& pos1,
                                           const Rectangle& rect2, const Point& pos2)
        {
            rectRectCalc calc;

            double half_width1 = rect1.getWidth() / 2.0;
            double half_height1 = rect1.getHeight() / 2.0;
            double half_width2 = rect2.getWidth() / 2.0;
            double half_height2 = rect2.getHeight() / 2.0;

            calc.diff = pos2 - pos1;
            calc.collision_point = Point(half_width1 + half_width2 - std::abs(calc.diff.x), 
                                        half_height1 + half_height2 - std::abs(calc.diff.y));

            return calc;
        }

        bool rectRect(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2, Info& info){
            const Rectangle& rect1 = static_cast<const Rectangle&>(shape1);
            const Rectangle& rect2 = static_cast<const Rectangle&>(shape2);

            const Point& pos1 = body1.getPosition();
            const Point& pos2 = body2.getPosition();
            
            rectRectCalc calc = preComputeRectRect(rect1, pos1, rect2, pos2);

            if(calc.collision_point.x <= 0 || calc.collision_point.y <= 0)
                return false;

            
            if(calc.collision_point.x < calc.collision_point.y){
                info.penetration = calc.collision_point.x;
                info.normal = (calc.diff.x > 0) ? DirVector(1,0) : DirVector(-1,0);
            }
            else{
                info.penetration = calc.collision_point.y;
                info.normal = (calc.diff.y > 0) ? DirVector(0,1) : DirVector(0,-1);
            }

            // TODO placeholder before implementing SAT
            info.contact_point = (pos1 + pos2) * 0.5;

            return true;
        }
    }
}