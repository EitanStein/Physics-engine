#pragma once

#include "PhysicsEngine/core/shapes/all_shapes.hpp"
#include "PhysicsEngine/core/body.hpp"
#include "resolve.hpp"
#include "info.hpp"

namespace Collision{

    using DetectFunc = bool(*)(const Shape&, const Body&, const Shape&, const Body&, Info&);

    DetectFunc getDetectFunc(ShapeT::Type shape1, ShapeT::Type shape2);

}