#pragma once
#include <windows.h>

namespace Security {
    // Overwrites DOS, NT, and Section headers with zeros
    void ErasePEHeader(HMODULE hModule);
}
