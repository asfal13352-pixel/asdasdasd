#pragma once
#include "Vector.hpp"

struct Matrix4x4 {
    float m[4][4];
    Vector3 Multiply(const Vector3& v) const {
        Vector3 out;
        out.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
        out.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
        out.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
        return out;
    }
};

inline bool WorldToScreen(const Vector3& pos, const Matrix4x4& viewProj, int width, int height, Vector2& out) {
    float clip_x = pos.x * viewProj.m[0][0] + pos.y * viewProj.m[1][0] + pos.z * viewProj.m[2][0] + viewProj.m[3][0];
    float clip_y = pos.x * viewProj.m[0][1] + pos.y * viewProj.m[1][1] + pos.z * viewProj.m[2][1] + viewProj.m[3][1];
    float clip_w = pos.x * viewProj.m[0][3] + pos.y * viewProj.m[1][3] + pos.z * viewProj.m[2][3] + viewProj.m[3][3];
    if (clip_w < 0.01f) return false;
    float ndc_x = clip_x / clip_w;
    float ndc_y = clip_y / clip_w;
    out.x = (ndc_x * 0.5f + 0.5f) * width;
    out.y = (1.0f - (ndc_y * 0.5f + 0.5f)) * height;
    return true;
}
