#include "DynImport.hpp"
#include <string>

namespace Security {
FARPROC DynImport(const char* obfModule, size_t modLen, const char* obfFunc, size_t funcLen) {
    std::string mod = Deobfuscate(obfModule, modLen);
    std::string fn = Deobfuscate(obfFunc, funcLen);
    HMODULE hMod = GetModuleHandleA(mod.c_str());
    if (!hMod) hMod = LoadLibraryA(mod.c_str());
    if (!hMod) return nullptr;
    return GetProcAddress(hMod, fn.c_str());
}
}
