#include "D3D11Hook.hpp"
#include <d3d11.h>
#include <dxgi.h>
#include "../Shared/IPCManager.hpp"
#include "../Shared/SharedRenderData.hpp"
#include "../Shared/Config.hpp"
#include "../Security/DynImport.hpp"
#include "../Shared/ObfStr.hpp"
#include <thread>
#include <atomic>
#include "MinHook.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

static std::atomic<bool> g_imguiInit{false};
static SharedRenderData g_renderData{};
static IPCManager* g_ipc = nullptr;

using Present_t = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
Present_t oPresent = nullptr;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void RenderOverlay(IDXGISwapChain* pSwapChain) {
    if (!g_imguiInit) {
        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* context = nullptr;
        pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&device);
        device->GetImmediateContext(&context);
        DXGI_SWAP_CHAIN_DESC sd;
        pSwapChain->GetDesc(&sd);
        ImGui::CreateContext();
        ImGui_ImplWin32_Init(sd.OutputWindow);
        ImGui_ImplDX11_Init(device, context);
        g_imguiInit = true;
    }
    if (g_ipc) g_ipc->Read(g_renderData);
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    // Draw ESP
    for (int i = 0; i < 64; ++i) {
        const auto& p = g_renderData.players[i];
        if (!p.valid) continue;
        if (g_renderData.config.visuals.boxes) {
            ImGui::GetBackgroundDrawList()->AddRect(
                ImVec2(p.box[0], p.box[1]), ImVec2(p.box[2], p.box[3]),
                IM_COL32(255,0,0,255));
        }
        if (g_renderData.config.visuals.health_bar) {
            float h = p.box[3] - p.box[1];
            float frac = p.health / 100.0f;
            ImGui::GetBackgroundDrawList()->AddRectFilled(
                ImVec2(p.box[0]-6, p.box[3] - h*frac),
                ImVec2(p.box[0]-2, p.box[3]), IM_COL32(0,255,0,255));
        }
        if (g_renderData.config.visuals.name_esp) {
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.box[0], p.box[1]-16), IM_COL32(255,255,255,255), p.name);
        }
        if (g_renderData.config.visuals.weapon_esp) {
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(p.box[0], p.box[3]+2), IM_COL32(200,200,200,255), p.weapon);
        }
    }
    // FOV circle
    ImGui::GetBackgroundDrawList()->AddCircle(
        ImVec2(g_renderData.aimbot_fov_circle[0], g_renderData.aimbot_fov_circle[1]),
        g_renderData.aimbot_fov_circle[2], IM_COL32(255,255,0,128), 64, 2.0f);
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT sync, UINT flags) {
    RenderOverlay(pSwapChain);
    return oPresent(pSwapChain, sync, flags);
}

void InitD3D11Hook(HMODULE) {
    // Dynamic API resolve
    auto GetModuleHandleA_ = (decltype(&GetModuleHandleA))Security::DynCast<void*>(OBFUSCATE("kernel32.dll"), 12, OBFUSCATE("GetModuleHandleA"), 16);
    auto GetProcAddress_ = (decltype(&GetProcAddress))Security::DynCast<void*>(OBFUSCATE("kernel32.dll"), 12, OBFUSCATE("GetProcAddress"), 14);
    auto CreateFileMappingA_ = (decltype(&CreateFileMappingA))Security::DynCast<void*>(OBFUSCATE("kernel32.dll"), 12, OBFUSCATE("CreateFileMappingA"), 18);
    auto MapViewOfFile_ = (decltype(&MapViewOfFile))Security::DynCast<void*>(OBFUSCATE("kernel32.dll"), 12, OBFUSCATE("MapViewOfFile"), 13);
    // MinHook setup
    MH_Initialize();
    // Find Present
    HMODULE hMod = GetModuleHandleA_("GameOverlayRenderer64.dll");
    void** vtbl = nullptr;
    // ... (Find Present address in vtable, omitted for brevity)
    // Suppose presentAddr is found
    void* presentAddr = nullptr; // Set to actual Present address
    MH_CreateHook(presentAddr, &hkPresent, reinterpret_cast<void**>(&oPresent));
    MH_EnableHook(presentAddr);
    g_ipc = new IPCManager("CS2_SharedMem");
    // Message loop for ImGui
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
