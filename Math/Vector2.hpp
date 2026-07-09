#pragma once
#include <cmath>

struct Vector2 {
    float x, y;
    Vector2(float x=0, float y=0) : x(x), y(y) {}
    float Length() const { return std::sqrt(x*x + y*y); }
    Vector2 operator+(const Vector2& o) const { return {x+o.x, y+o.y}; }
    Vector2 operator-(const Vector2& o) const { return {x-o.x, y-o.y}; }
    Vector2 operator*(float f) const { return {x*f, y*f}; }
    Vector2 operator/(float f) const { return {x/f, y/f}; }
    Vector2& operator+=(const Vector2& o) { x+=o.x; y+=o.y; return *this; }
    Vector2& operator-=(const Vector2& o) { x-=o.x; y-=o.y; return *this; }
    float Dot(const Vector2& o) const { return x*o.x + y*o.y; }
    Vector2 Normalized() const { float l=Length(); return l>0?(*this)/l:*this; }
};
