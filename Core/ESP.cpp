#include "ESP.hpp"
#include <cstring>

void FillESPData(const Entity* ents, int num, int localIdx, SharedRenderData& out, int screenW, int screenH) {
    out.localPlayerIdx = localIdx;
    for (int i = 0; i < num; ++i) {
        auto& p = out.players[i];
        const auto& e = ents[i];
        p.valid = e.valid;
        p.health = e.health;
        p.team = e.team;
        p.box[0] = e.origin.x - 20; // left
        p.box[1] = e.origin.y - 40; // top
        p.box[2] = e.origin.x + 20; // right
        p.box[3] = e.origin.y + 40; // bottom
        p.head_screen[0] = e.head.x;
        p.head_screen[1] = e.head.y;
        p.origin_screen[0] = e.origin.x;
        p.origin_screen[1] = e.origin.y;
        std::strncpy(p.name, e.name, 32);
        std::strncpy(p.weapon, e.weapon, 32);
        p.visible = e.visible;
        p.in_smoke = e.in_smoke;
    }
}
