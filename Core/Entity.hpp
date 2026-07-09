#pragma once
#include <cstdint>
#include "../Math/Vector.hpp"
#include "../Math/Matrix.hpp"

// Forward declaration so compiler knows 'Memory' exists
class Memory; 

struct Entity {
    uintptr_t base;
    int health;
    int team;
    Vector3 origin;
    Vector3 head;
    char name[32];
    char weapon[32];
    bool visible;
    bool in_smoke;
    bool valid;
};

bool ReadEntity(uintptr_t entBase, Entity& out, const Memory& mem, uintptr_t viewMatrix, int screenW, int screenH);
bool IsVisible(const Entity& ent, const Memory& mem, uintptr_t localPlayerBase);
bool IsInSmoke(const Entity& ent, const Memory& mem);