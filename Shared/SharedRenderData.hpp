#pragma once
#include <cstdint>
#include <array>
#include "Config.hpp"

inline constexpr int MAX_PLAYERS = 64;
constexpr int MAX_NAME_LEN = 32;
constexpr int MAX_WEAPON_LEN = 32;

struct PlayerRenderInfo {
    bool valid;
    int health;
    int team;
    float box[4]; // left, top, right, bottom
    float head_screen[2];
    float origin_screen[2];
    char name[MAX_NAME_LEN];
    char weapon[MAX_WEAPON_LEN];
    bool visible;
    bool in_smoke;
};

struct SharedRenderData {
    Config config;
    int localPlayerIdx;
    std::array<PlayerRenderInfo, MAX_PLAYERS> players;
    // For overlay visuals (e.g., aimbot FOV)
    float aimbot_fov_circle[3]; // x, y, radius
    uint32_t frame_id;
};
