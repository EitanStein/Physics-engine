#pragma once

#include "base_shape.hpp"
#include <array>
#include <cmath> // TODO move to cpp file

class Rectangle : public Shape{
private:
    double width;
    double height;

    double half_width;
    double half_height;

    double bounding_radius;
public:
    Rectangle(double width, double height) : width(width), height(height),
                                              half_width(width/2), half_height(height/2) {
        bounding_radius = sqrt(half_width*half_width + half_height*half_height);
    }
    double getWidth() const {return width;}
    double getHeight() const {return height;}

    double getHalfWidth() const {return half_width;};
    double getHalfHeight() const {return half_height;};
    
    double boundingRadius() const override {return bounding_radius;}

    bool contains(const Point& pos, const Point& point) const override { 
        return (std::abs(pos.x - point.x) <= half_width) && (std::abs(pos.y - point.y) <= half_height);
    }
    ShapeT::Type type() const override {return ShapeT::Type::Rectangle; }

    std::array<Point,4> getVertices(const Point& pos, double angle) const{
        std::array<Point,4> vertices = {
            Point(-half_width, -half_height),
            Point(half_width, -half_height),
            Point(half_width, half_height),
            Point(-half_width, half_height)
        };

        rotate(vertices, angle);

        for (auto& v : vertices)
            v += pos;

        return vertices;
    }
};