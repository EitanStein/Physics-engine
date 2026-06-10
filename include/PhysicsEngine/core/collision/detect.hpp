#pragma once

#include "../body.hpp"
#include "PhysicsEngine/core/shapes/all_shapes.hpp"
#include "info.hpp"

// TODO maybe return collision info instead of just detecting collision and returning bool
// collision info could include 'is colliding', 'collision point', 'collision normal' and more
namespace Collision{
    namespace Detect{
        inline constexpr bool isBoundingRadiusColliding(const DirVector& center_diff, double bounding_rad1, double bounding_rad2){
            return dotProduct(center_diff, center_diff) < std::pow(bounding_rad1 + bounding_rad2, 2);
        }

        inline constexpr bool isBoundingRadiusColliding(const Shape& shape1, const Body& body1, const Shape& shape2, const Body& body2){
            return squaredDist(body1.getPosition(), body2.getPosition()) < std::pow(shape1.boundingRadius() + shape2.boundingRadius(), 2);
        } 

        bool circleCircle(const Shape& circle1, const Body& body1, const Shape& circle2, const Body& body2, Info& info);
        bool circleRect(const Shape& circle, const Body& body1, const Shape& rect, const Body& body2, Info& info);

        bool rectCircle(const Shape& rect, const Body& body1, const Shape& circle, const Body& body2, Info& info);
        bool rectRect(const Shape& rect1, const Body& body1, const Shape& rect2, const Body& body2, Info& info);
    }
}