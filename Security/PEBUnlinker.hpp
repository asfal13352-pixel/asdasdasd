#pragma once
#include <windows.h>

namespace Security {
    // Unlinks the module from the PEB module lists
    void UnlinkFromPEB(HMODULE hModule);
}
