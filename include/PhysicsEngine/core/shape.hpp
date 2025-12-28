#pragma once

#include "point.hpp"

class Shape {
public:
    virtual bool contains(const Point& pos, const Point& point) const {return false;};
};

class Circle : public Shape{
private:
    double radius;
public:
    Circle(double radius) : radius(radius) {}
    double getRadius() const {return radius;}
    bool contains(const Point& pos, const Point& point) const override { return dist(pos, point) <= radius;}
};