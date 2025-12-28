#pragma once

struct Point{
    double x;
    double y;

    Point(double x=0, double y=0) : x(x), y(y) {}

    Point(const Point&) = default;
    Point(Point&&) = default;
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) = default;

    Point operator*(double num) {return Point(x*num, y*num);}
    Point operator/(double num) {return Point(x/num, y/num);}
    Point operator+(const Point& other) {return Point(x+other.x, y+other.y);}
    Point operator-(const Point& other) {return Point(x-other.x, y-other.y);}
    void operator+=(const Point& other) {x+=other.x; y+=other.y;}
    void operator*=(double num) {x*=num; y*=num;}
    bool operator==(const Point& other) const {return (x == other.x && y == other.y);}
};

typedef Point DirVector;

double dist(const Point& first, const Point& second){ // TODO change dist function
    double x_dist = (first.x > second.x) ? first.x - second.x : second.x - first.x;
    double y_dist = (first.y > second.y) ? first.y - second.y : second.y - first.y;
    return x_dist + y_dist;
}