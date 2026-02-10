#pragma once

#include "PhysicsEngine/core/point.hpp"

class Shape {
public:
    virtual bool contains(const Point& pos, const Point& point) const {return false;};
};