#pragma once

#include "base_shape.hpp"
#include <cmath> // TODO move to cpp file

class Rectangle : public Shape{
private:
    double width;
    double height;
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    double getWidth() const {return width;}
    double getHeight() const {return height;}
    bool contains(const Point& pos, const Point& point) const override { 
        return (std::abs(pos.x - point.x) <= width/2) && (std::abs(pos.y - point.y) <= height/2);
    }
    ShapeT::Type type() const override {return ShapeT::Type::Rectangle; }
};