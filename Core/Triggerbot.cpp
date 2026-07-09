#include "Triggerbot.hpp"
#include <thread>

bool Triggerbot::ShouldShoot(const Entity& ent) {
    using namespace std::chrono;
    if (!config.triggerbot.enabled) return false;
    if (config.triggerbot.visibility_check && !ent.visible) return false;
    if (config.triggerbot.smoke_check && ent.in_smoke) return false;
    auto now = steady_clock::now();
    if (duration_cast<milliseconds>(now - lastShot).count() < config.triggerbot.shot_interval_ms)
        return false;
    std::this_thread::sleep_for(milliseconds(config.triggerbot.reaction_delay_ms));
    lastShot = steady_clock::now();
    return true;
}
