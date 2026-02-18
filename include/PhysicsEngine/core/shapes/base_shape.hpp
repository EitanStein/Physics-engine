#pragma once

#include "PhysicsEngine/core/point.hpp"

// TODO merge all shape related stuff under one namespace?
// change namespace name
namespace ShapeT{
    enum class Type{Circle, NumTypes};
    constexpr size_t NUM_SHAPES = static_cast<size_t>(Type::NumTypes);

    inline bool isValidType(Type shape){
        return static_cast<size_t>(shape) < NUM_SHAPES;
    }
}


class Shape {
public:
    virtual bool contains(const Point& pos, const Point& point) const {return false;};
    virtual ShapeT::Type type() const = 0;
};

