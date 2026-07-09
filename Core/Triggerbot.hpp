#pragma once
#include "Entity.hpp"
#include "../Shared/Config.hpp"
#include <chrono>

class Triggerbot {
public:
    Triggerbot(const Config& cfg) : config(cfg), lastShot(0) {}
    bool ShouldShoot(const Entity& ent);
private:
    const Config& config;
    std::chrono::steady_clock::time_point lastShot;
};
