#pragma once
#include <windows.h>
#include <string>
#include "../Shared/ObfStr.hpp"
#include "DynImport.hpp"

namespace Security {
    // Dynamically resolves an API from a module using obfuscated strings
    FARPROC DynImport(const char* obfModule, size_t modLen, const char* obfFunc, size_t funcLen);
    template<typename T>
    T DynCast(const char* obfModule, size_t modLen, const char* obfFunc, size_t funcLen) {
        return reinterpret_cast<T>(DynImport(obfModule, modLen, obfFunc, funcLen));
    }
}
