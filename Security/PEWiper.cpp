#include "PEWiper.hpp"
#include <winnt.h>
#include <cstring>
#include <cstdint>

namespace Security {
void ErasePEHeader(HMODULE hModule) {
    if (!hModule) return;
    auto* base = reinterpret_cast<uint8_t*>(hModule);
    auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return;
    auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
    DWORD old;
    // DOS header
    VirtualProtect(base, sizeof(IMAGE_DOS_HEADER), PAGE_EXECUTE_READWRITE, &old);
    std::memset(base, 0, sizeof(IMAGE_DOS_HEADER));
    // NT headers
    VirtualProtect(nt, sizeof(IMAGE_NT_HEADERS), PAGE_EXECUTE_READWRITE, &old);
    std::memset(nt, 0, sizeof(IMAGE_NT_HEADERS));
    // Section headers
    auto* sec = IMAGE_FIRST_SECTION(nt);
    for (int i = 0; i < nt->FileHeader.NumberOfSections; ++i) {
        VirtualProtect(sec, sizeof(IMAGE_SECTION_HEADER), PAGE_EXECUTE_READWRITE, &old);
        std::memset(sec, 0, sizeof(IMAGE_SECTION_HEADER));
        ++sec;
    }
}
}
