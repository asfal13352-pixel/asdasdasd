#include "Memory.hpp"
#include <tlhelp32.h>

static DWORD FindProcessId(const std::wstring& name) {
    PROCESSENTRY32W entry{sizeof(entry)};
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return 0;
    if (Process32FirstW(snap, &entry)) {
        do {
            if (name == entry.szExeFile) {
                CloseHandle(snap);
                return entry.th32ProcessID;
            }
        } while (Process32NextW(snap, &entry));
    }
    CloseHandle(snap);
    return 0;
}

Memory::Memory(const std::wstring& procName) {
    pid = FindProcessId(procName);
    if (!pid) return;
    hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
}
Memory::~Memory() { if (hProcess) CloseHandle(hProcess); }
bool Memory::Read(uintptr_t addr, void* buf, size_t sz) const {
    SIZE_T r;
    return ReadProcessMemory(hProcess, (LPCVOID)addr, buf, sz, &r) && r == sz;
}
