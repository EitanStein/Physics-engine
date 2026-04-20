#pragma once

#include "base_shape.hpp"
#include <array>
#include <cmath> // TODO move to cpp file

class Rectangle : public Shape{
private:
    double width;
    double height;

    // TODO change all /2 with these
    // double half_width;
    // double half_height;
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    double getWidth() const {return width;}
    double getHeight() const {return height;}
    bool contains(const Point& pos, const Point& point) const override { 
        return (std::abs(pos.x - point.x) <= width/2) && (std::abs(pos.y - point.y) <= height/2);
    }
    ShapeT::Type type() const override {return ShapeT::Type::Rectangle; }

    std::array<Point,4> getVertices(const Point& pos, double angle) const{
        double half_width = width / 2.0;
        double half_height = height / 2.0;

        double cos_angle = std::cos(angle);
        double sin_angle = std::sin(angle);

        std::array<Point,4> vertices = {
            Point(-half_width, -half_height),
            Point(half_width, -half_height),
            Point(half_width, half_height),
            Point(-half_width, half_height)
        };

        for (auto& v : vertices)
        {
            double x = v.x;
            double y = v.y;

            v.x = x*cos_angle - y*sin_angle;
            v.y = x*sin_angle + y*cos_angle;

            v += pos;
        }

        return vertices;
    }
};