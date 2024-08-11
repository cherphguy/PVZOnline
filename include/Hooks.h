#pragma once

#include "MinHook.h"
#include "vector"
#include <expected>

struct HookManager {
    public:
    MH_STATUS Initialize();
    template <typename T>
    MH_STATUS CreateHook(void** target, T detour);
    template <typename T>
    static std::expected<T, MH_STATUS> GetOriginalFunction(void** target);
    MH_STATUS RemoveHook(void** target); 
    MH_STATUS EnableHook(void** target);
    MH_STATUS DisableHook(void** target);
    MH_STATUS EnableAllHooks();
};