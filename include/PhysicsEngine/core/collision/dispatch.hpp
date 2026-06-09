#pragma once

#include "PhysicsEngine/core/shapes/all_shapes.hpp"
#include "PhysicsEngine/core/body.hpp"
#include "info.hpp"

namespace Collision{
    bool isColliding(const Shape&, const Body&, const Shape&, const Body&, Info&);
}