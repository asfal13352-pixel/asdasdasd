#pragma once
#include "Entity.hpp"
#include "../Math/Vector2.hpp"
#include "../Math/Bezier.hpp"
#include "../Math/Smoothing.hpp"
#include "../Shared/Config.hpp"

class Aimbot {
public:
    Aimbot(const Config& cfg) : config(cfg) {}
    bool FindTarget(const Entity* ents, int num, int localIdx, int& outIdx, Vector2& outScreen, int screenW, int screenH);
    Vector2 GetAimDelta(const Vector2& from, const Vector2& to);
private:
    const Config& config;
};
