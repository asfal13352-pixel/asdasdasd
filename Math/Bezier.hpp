#pragma once
#include "Vector2.hpp"
#include <array>

// Cubic Bezier curve for aimbot smoothing
inline Vector2 Bezier3(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, float t) {
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;
    return p0 * uuu + p1 * 3 * uu * t + p2 * 3 * u * tt + p3 * ttt;
}
