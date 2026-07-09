#include "Aimbot.hpp"
#include <limits>
#include <cmath>

bool Aimbot::FindTarget(const Entity* ents, int num, int localIdx, int& outIdx, Vector2& outScreen, int screenW, int screenH) {
    float bestDist = config.aimbot.fov;
    bool found = false;
    for (int i = 0; i < num; ++i) {
        if (i == localIdx || !ents[i].valid || ents[i].team == ents[localIdx].team) continue;
        if (config.aimbot.visibility_check && !ents[i].visible) continue;
        if (config.aimbot.smoke_check && ents[i].in_smoke) continue;
        Vector2 screenPos(ents[i].head.x, ents[i].head.y);
        float dist = std::hypot(screenPos.x - screenW/2, screenPos.y - screenH/2);
        if (dist < bestDist) {
            bestDist = dist;
            outIdx = i;
            outScreen = screenPos;
            found = true;
        }
    }
    return found;
}

Vector2 Aimbot::GetAimDelta(const Vector2& from, const Vector2& to) {
    // Bezier + smoothing
    Vector2 cp1 = from + (to-from)*0.3f;
    Vector2 cp2 = from + (to-from)*0.6f;
    float t = 0.5f;
    Vector2 bez = Bezier3(from, cp1, cp2, to, t);
    return HumanSmooth(from, bez, config.aimbot.smooth_x, config.aimbot.smooth_y) - from;
}
