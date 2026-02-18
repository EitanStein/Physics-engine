#pragma once

#include "PhysicsEngine/core/shapes/all_shapes.hpp"
#include "../body.hpp"

namespace Collision{

    using DetectFunc = bool(*)(const Shape&, const Point&, const Shape&, const Point&);
    using ResolveFunc = void(*)(const Shape&, Body&, const Shape&, Body&);

    DetectFunc getDetectFunc(ShapeT::Type shape1, ShapeT::Type shape2);

    ResolveFunc getResolveFunc(ShapeT::Type shape1, ShapeT::Type shape2);

}