#pragma once

#include "PhysicsEngine/core/point.hpp"
#include "PhysicsEngine/core/shapes/all_shapes.hpp"

namespace Collision{
    struct Info{
        DirVector normal;
        double penetration = 0;
        Point contact_point;

        constexpr bool operator==(const Info& other) const{
            return (normal == other.normal && penetration == other.penetration && contact_point == other.contact_point);
        }
    };
}