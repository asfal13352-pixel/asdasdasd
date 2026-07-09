#include <windows.h>
#include "../Security/PEWiper.hpp"
#include "../Security/PEBUnlinker.hpp"
#include "../Security/DynImport.hpp"
#include "D3D11Hook.hpp"
#include "MinHook.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        Security::ErasePEHeader(hModule);
        Security::UnlinkFromPEB(hModule);
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitD3D11Hook, hModule, 0, nullptr);
    }
    return TRUE;
}
