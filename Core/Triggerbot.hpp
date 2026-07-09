#pragma once
#include "Entity.hpp"
#include "../Shared/Config.hpp"
#include <chrono>

class Triggerbot {
public:
    // Change lastShot(0) -> lastShot{}
    Triggerbot(const Config& cfg) : config(cfg), lastShot{} {}
    
    bool ShouldShoot(const Entity& ent);

private:
    const Config& config;
    std::chrono::steady_clock::time_point lastShot;
};