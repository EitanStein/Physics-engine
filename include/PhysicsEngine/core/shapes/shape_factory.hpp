#pragma once

#include "all_shapes.hpp"
#include <memory>
#include "PhysicsEngine/logging/log_macros.hpp"


struct ShapeFactory{
    static std::unique_ptr<Shape> createCircle(double radius){
        if(radius <= 0){
            LOG_ERROR("Circle radius must be positive");
            return nullptr;
        }
        return std::make_unique<Circle>(radius);
    }
};