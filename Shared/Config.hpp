#pragma once
#include <cstdint>

struct AimbotConfig {
    bool enabled;
    int bind_key;
    float fov;
    float smooth_x, smooth_y;
    int target_bone;
    bool target_randomizer;
    bool visibility_check;
    bool smoke_check;
};

struct TriggerbotConfig {
    bool enabled;
    int bind_key;
    int reaction_delay_ms;
    int shot_interval_ms;
    bool visibility_check;
    bool smoke_check;
};

struct VisualsConfig {
    bool boxes;
    bool health_bar;
    bool name_esp;
    bool weapon_esp;
};

struct Config {
    AimbotConfig aimbot;
    TriggerbotConfig triggerbot;
    VisualsConfig visuals;
};
