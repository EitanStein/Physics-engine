#pragma once

#include <cmath>
#include <array>

struct Point{
    double x;
    double y;

    Point(double x=0, double y=0) : x(x), y(y) {}

    Point(const Point&) = default;
    Point(Point&&) = default;
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) = default;

    Point operator*(double num) const {return Point(x*num, y*num);}
    Point operator/(double num) const {return Point(x/num, y/num);}
    Point operator+(const Point& other) const {return Point(x+other.x, y+other.y);}
    Point operator-(const Point& other) const {return Point(x-other.x, y-other.y);}
    void operator+=(const Point& other) {x+=other.x; y+=other.y;}
    void operator*=(double num) {x*=num; y*=num;}
    bool operator==(const Point& other) const {return (x == other.x && y == other.y);}
};

typedef Point DirVector;

inline double dist(const Point& p1, const Point& p2){ 
    return std::sqrt(std::pow(p1.x  - p2.x, 2) + std::pow(p1.y  - p2.y, 2));
}

inline double dotProduct(const Point& p1, const Point& p2){
    return p1.x * p2.x + p1.y * p2.y;
}

inline double cross(const DirVector& a, const DirVector& b){
    return a.x * b.y - a.y * b.x;
}

inline DirVector cross(double s, const DirVector& v){
    return DirVector(-s * v.y, s * v.x);
}

inline DirVector normalize(const DirVector& v) {
    double len = std::sqrt(dotProduct(v,v));
    if (len == 0) return DirVector(0,0);
    return v / len;
}

inline DirVector perpendicular(const DirVector& v) {
    return DirVector(-v.y, v.x);
}

inline void rotate(DirVector& v, double angle){
    double cos_angle = std::cos(angle);
    double sin_angle = std::sin(angle);

    DirVector copy = v;

    v.x = copy.x*cos_angle - copy.y*sin_angle;
    v.y = copy.x*sin_angle + copy.y*cos_angle;

}

// TODO template based on size or use something instead of std::array
inline void rotate(std::array<DirVector, 4>& arr_v, double angle){
    double cos_angle = std::cos(angle);
    double sin_angle = std::sin(angle);

    for (auto& v : arr_v){
        DirVector copy = v;
        v.x = copy.x*cos_angle - copy.y*sin_angle;
        v.y = copy.x*sin_angle + copy.y*cos_angle;
    }  
}