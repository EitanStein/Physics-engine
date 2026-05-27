#pragma once

#include "PhysicsEngine/core/point.hpp"

// TODO merge all shape related stuff under one namespace?
// change namespace name
namespace ShapeT{
    enum class Type{Circle, Rectangle, NumTypes};
    constexpr size_t NUM_SHAPES = static_cast<size_t>(Type::NumTypes);

    inline bool isValidType(Type shape){
        return static_cast<size_t>(shape) < NUM_SHAPES;
    }
}


class Shape {
public:
    virtual bool contains([[maybe_unused]] const Point& pos,[[maybe_unused]] const Point& point) const {return false;};
    virtual ShapeT::Type type() const = 0;
    virtual ~Shape() = default;
};

