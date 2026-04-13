#pragma once

#include "PhysicsEngine/core/shapes/all_shapes.hpp"
#include "PhysicsEngine/core/body.hpp"
#include "resolve.hpp"
#include "info.hpp"

namespace Collision{

    using DetectFunc = bool(*)(const Shape&, const Point&, const Shape&, const Point&, Info&);

    DetectFunc getDetectFunc(ShapeT::Type shape1, ShapeT::Type shape2);

}