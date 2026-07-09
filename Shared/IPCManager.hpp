#pragma once
#include <windows.h>
#include <string>
#include "SharedRenderData.hpp"

class IPCManager {
public:
    IPCManager(const std::string& shm_name);
    ~IPCManager();

    bool Write(const SharedRenderData& data);
    bool Read(SharedRenderData& out);

private:
    HANDLE hMapFile = nullptr;
    HANDLE hMutex = nullptr;
    SharedRenderData* pData = nullptr;
    std::string shmName;
    std::string mutexName;
};
