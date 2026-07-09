#include "PEBUnlinker.hpp"
#include <winternl.h>

namespace Security {
struct LIST_ENTRY32 {
    LIST_ENTRY32* Flink;
    LIST_ENTRY32* Blink;
};

struct LDR_DATA_TABLE_ENTRY32 {
    LIST_ENTRY32 InLoadOrderLinks;
    LIST_ENTRY32 InMemoryOrderLinks;
    LIST_ENTRY32 InInitializationOrderLinks;
    void* DllBase;
    // ...
};

void UnlinkFromPEB(HMODULE hModule) {
    PPEB peb = (PPEB)__readgsqword(0x60);
    auto ldr = peb->Ldr;
    auto head = (PLIST_ENTRY)(&ldr->InMemoryOrderModuleList);
    for (PLIST_ENTRY curr = head->Flink; curr != head; curr = curr->Flink) {
        auto entry = CONTAINING_RECORD(curr, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
        if (entry->DllBase == hModule) {
            // Unlink
            curr->Blink->Flink = curr->Flink;
            curr->Flink->Blink = curr->Blink;
            break;
        }
    }
}
}
