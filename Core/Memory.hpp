#pragma once
#include <windows.h>
#include <cstdint>
#include <vector>
#include <string>

class Memory {
public:
    Memory(const std::wstring& procName);
    ~Memory();
    bool IsValid() const { return hProcess != nullptr; }
    bool Read(uintptr_t addr, void* buf, size_t sz) const;
    template<typename T> bool Read(uintptr_t addr, T& out) const { return Read(addr, &out, sizeof(T)); }
    DWORD GetPID() const { return pid; }
private:
    HANDLE hProcess = nullptr;
    DWORD pid = 0;
};
