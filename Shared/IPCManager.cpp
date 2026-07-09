#include "IPCManager.hpp"
#include <cstring>
#include <stdexcept>
#include <windows.h>

IPCManager::IPCManager(const std::string& shm_name) : shmName(shm_name), mutexName(shm_name + "_mtx") {
    hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(SharedRenderData), shmName.c_str());
    if (!hMapFile) throw std::runtime_error("Failed to create shared memory");
    pData = reinterpret_cast<SharedRenderData*>(MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedRenderData)));
    if (!pData) throw std::runtime_error("Failed to map shared memory");
    hMutex = CreateMutexA(nullptr, FALSE, mutexName.c_str());
    if (!hMutex) throw std::runtime_error("Failed to create mutex");
}

IPCManager::~IPCManager() {
    if (pData) UnmapViewOfFile(pData);
    if (hMapFile) CloseHandle(hMapFile);
    if (hMutex) CloseHandle(hMutex);
}

bool IPCManager::Write(const SharedRenderData& data) {
    if (WaitForSingleObject(hMutex, 10) == WAIT_OBJECT_0) {
        std::memcpy(pData, &data, sizeof(SharedRenderData));
        ReleaseMutex(hMutex);
        return true;
    }
    return false;
}

bool IPCManager::Read(SharedRenderData& out) {
    if (WaitForSingleObject(hMutex, 10) == WAIT_OBJECT_0) {
        std::memcpy(&out, pData, sizeof(SharedRenderData));
        ReleaseMutex(hMutex);
        return true;
    }
    return false;
}
