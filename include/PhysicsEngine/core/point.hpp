#pragma once

#include <cmath>
#include <array>

struct Point{
    double x;
    double y;

    constexpr Point operator*(double num) const {return Point{x*num, y*num};}
    constexpr Point operator/(double num) const {return Point{x/num, y/num};}
    constexpr Point operator+(const Point& other) const {return Point{x+other.x, y+other.y};}
    constexpr Point operator-(const Point& other) const {return Point{x-other.x, y-other.y};}
    constexpr void operator+=(const Point& other) {x+=other.x; y+=other.y;}
    constexpr void operator*=(double num) {x*=num; y*=num;}
    constexpr bool operator==(const Point& other) const {return (x == other.x && y == other.y);}
};

typedef Point DirVector;
// TODO namespace?
inline constexpr double dist(const Point& p1, const Point& p2){ 
    return std::sqrt(std::pow(p1.x  - p2.x, 2) + std::pow(p1.y  - p2.y, 2));
}

inline constexpr double squaredDist(const Point& p1, const Point& p2){ 
    return std::pow(p1.x  - p2.x, 2) + std::pow(p1.y  - p2.y, 2);
}

inline constexpr double dotProduct(const Point& p1, const Point& p2){
    return p1.x * p2.x + p1.y * p2.y;
}

inline constexpr double cross(const DirVector& a, const DirVector& b){
    return a.x * b.y - a.y * b.x;
}

inline constexpr DirVector cross(double s, const DirVector& v){
    return DirVector{-s * v.y, s * v.x};
}

inline constexpr DirVector normalize(const DirVector& v) {
    double len = std::sqrt(dotProduct(v,v));
    if (len == 0) return DirVector{0,0};
    return v / len;
}

inline constexpr DirVector perpendicular(const DirVector& v) {
    return DirVector{-v.y, v.x};
}

inline constexpr DirVector rotate(const DirVector& v, double angle){
    double cos_angle = std::cos(angle);
    double sin_angle = std::sin(angle);

    return {v.x*cos_angle - v.y*sin_angle,
            v.x*sin_angle + v.y*cos_angle};
}

// TODO template based on size or use something instead of std::array
inline constexpr void rotate(std::array<DirVector, 4>& arr_v, double angle){
    double cos_angle = std::cos(angle);
    double sin_angle = std::sin(angle);

    for (auto& v : arr_v){
        DirVector copy = v;
        v.x = copy.x*cos_angle - copy.y*sin_angle;
        v.y = copy.x*sin_angle + copy.y*cos_angle;
    }  
}