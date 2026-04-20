#pragma once

#include "PhysicsEngine/core/point.hpp"
#include "PhysicsEngine/core/shapes/all_shapes.hpp"

namespace Collision{
    struct Info{
        DirVector normal;
        double penetration = 0;
        Point contact_point;
    };
}