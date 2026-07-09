#include "Entity.hpp"
#include "Memory.hpp"
#include <cstring>

// Dummy offsets for illustration; replace with CS2Offsets/ values in integration
constexpr uintptr_t m_iHealth = 0x334;
constexpr uintptr_t m_iTeamNum = 0x3C4;
constexpr uintptr_t m_vOldOrigin = 0x1224;
constexpr uintptr_t m_bSpotted = 0x93D;
constexpr uintptr_t m_pClippingWeapon = 0x12C8;

bool ReadEntity(uintptr_t entBase, Entity& out, const Memory& mem, uintptr_t viewMatrix, int screenW, int screenH) {
    if (!entBase) return false;
    out.base = entBase;
    mem.Read(entBase + m_iHealth, out.health);
    mem.Read(entBase + m_iTeamNum, out.team);
    mem.Read(entBase + m_vOldOrigin, out.origin);
    // Head bone: for demo, just offset Z
    out.head = out.origin; out.head.z += 64.0f;
    // Name/weapon: stub
    std::strncpy(out.name, "Player", 32);
    std::strncpy(out.weapon, "AK-47", 32);
    // Visibility/smoke: stub
    out.visible = true;
    out.in_smoke = false;
    out.valid = out.health > 0;
    return out.valid;
}

bool IsVisible(const Entity& ent, const Memory& mem, uintptr_t localPlayerBase) {
    // Use m_bSpotted or ray checks in real impl
    return ent.visible;
}

bool IsInSmoke(const Entity& ent, const Memory& mem) {
    // Use smoke volume checks in real impl
    return ent.in_smoke;
}
