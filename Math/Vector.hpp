#pragma once
#include <cmath>

struct Vector3 {
    float x, y, z;
    Vector3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {}
    float Length() const { return std::sqrt(x*x + y*y + z*z); }
    Vector3 operator+(const Vector3& o) const { return {x+o.x, y+o.y, z+o.z}; }
    Vector3 operator-(const Vector3& o) const { return {x-o.x, y-o.y, z-o.z}; }
    Vector3 operator*(float f) const { return {x*f, y*f, z*f}; }
    Vector3 operator/(float f) const { return {x/f, y/f, z/f}; }
    Vector3& operator+=(const Vector3& o) { x+=o.x; y+=o.y; z+=o.z; return *this; }
    Vector3& operator-=(const Vector3& o) { x-=o.x; y-=o.y; z-=o.z; return *this; }
    float Dot(const Vector3& o) const { return x*o.x + y*o.y + z*o.z; }
    Vector3 Cross(const Vector3& o) const { return {y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x}; }
    Vector3 Normalized() const { float l=Length(); return l>0?(*this)/l:*this; }
};

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
