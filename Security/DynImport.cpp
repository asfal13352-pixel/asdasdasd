#include "DynImport.hpp"
#include "../Shared/ObfStr.hpp"

namespace Security {
    FARPROC DynImport(const char* obfModule, size_t modLen, const char* obfFunc, size_t funcLen) {
        // If you need to deobfuscate in here, wrap the raw pointer inside an ObfStr instance or standard XOR loop:
        // Example:
        std::string moduleName;
        for (size_t i = 0; i < modLen; ++i) {
            moduleName += static_cast<char>(obfModule[i] ^ 0xAA);
        }

        std::string funcName;
        for (size_t i = 0; i < funcLen; ++i) {
            funcName += static_cast<char>(obfFunc[i] ^ 0xAA);
        }

        HMODULE hMod = GetModuleHandleA(moduleName.c_str());
        if (!hMod) {
            hMod = LoadLibraryA(moduleName.c_str());
        }

        return hMod ? GetProcAddress(hMod, funcName.c_str()) : nullptr;
    }
}