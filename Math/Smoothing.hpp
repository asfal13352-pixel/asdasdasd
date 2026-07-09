#pragma once
#include "Vector2.hpp"
#include "Random.hpp"

// Asymmetric smoothing with micro-variation
inline Vector2 HumanSmooth(const Vector2& from, const Vector2& to, float smooth_x, float smooth_y) {
    Vector2 delta = to - from;
    delta.x /= smooth_x;
    delta.y /= smooth_y;
    // Add Gaussian micro-variation
    delta.x += RandGaussian(0.0f, 0.2f);
    delta.y += RandGaussian(0.0f, 0.2f);
    return from + delta;
}
