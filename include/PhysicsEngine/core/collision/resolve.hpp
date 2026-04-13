#pragma once

#include "../body.hpp"
#include "PhysicsEngine/core/shapes/all_shapes.hpp"
#include "info.hpp"

namespace Collision{
    namespace Resolve{
        void resolve(Body& body1, Body& body2, const Info& info);
    }
}