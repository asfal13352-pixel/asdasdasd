#include <windows.h>
#include <vector>
#include <thread>

#include "Memory.hpp"
#include "Entity.hpp"
#include "Aimbot.hpp"
#include "Triggerbot.hpp"
#include "ESP.hpp"

#include "../Math/Vector.hpp"
#include "../Shared/Config.hpp"
#include "../Shared/SharedRenderData.hpp"
#include "../Shared/IPCManager.hpp"

const int screenW = GetSystemMetrics(SM_CXSCREEN);
const int screenH = GetSystemMetrics(SM_CYSCREEN);

int main() {
    Memory mem(L"cs2.exe");
    if (!mem.IsValid()) return 1;
    Config config = {/*... fill with your config ...*/};
    IPCManager ipc("CS2_SharedMem");
    std::vector<Entity> ents(MAX_PLAYERS);
    int localIdx = 0;
    Aimbot aimbot(config);
    Triggerbot triggerbot(config);
    SharedRenderData renderData{};
    while (true) {
        // Read entities
        for (int i = 0; i < MAX_PLAYERS; ++i) {
            uintptr_t entBase = 0; // Read from EntityList
            ReadEntity(entBase, ents[i], mem, 0, screenW, screenH);
        }
        // Aimbot
        int targetIdx = -1;
        Vector2 aimScreen;
        if (aimbot.FindTarget(ents.data(), MAX_PLAYERS, localIdx, targetIdx, aimScreen, screenW, screenH)) {
            // Move mouse using SendInput (not implemented here)
        }
        // Triggerbot
        if (targetIdx != -1 && triggerbot.ShouldShoot(ents[targetIdx])) {
            // Fire using SendInput (not implemented here)
        }
        // ESP
        FillESPData(ents.data(), MAX_PLAYERS, localIdx, renderData, screenW, screenH);
        ipc.Write(renderData);
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }
    return 0;
}
