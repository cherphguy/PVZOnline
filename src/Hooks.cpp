#include "Hooks.h"
#include "MinHook.h"
MH_STATUS HookManager::Initialize() {
    return MH_Initialize();
};

template <typename T>
MH_STATUS HookManager::CreateHook(void** target, T detour) {
    void** Original = nullptr;
    return MH_CreateHook(target, reinterpret_cast<void**>(detour), Original);
};

template <typename T>
static std::expected<T, MH_STATUS> HookManager::GetOriginalFunction(void** target) {
    T original;
    MH_STATUS status = MH_GetOriginalFunction(target, reinterpret_cast<void**>(&original));
    if (status != MH_OK) {
        return std::unexpected(status);
    }
    return original;
}

MH_STATUS HookManager::RemoveHook(void** target) {
    return MH_RemoveHook(target);
}

MH_STATUS HookManager::EnableHook(void** target){
    return MH_EnableHook(target);
}

MH_STATUS HookManager::DisableHook(void** target) {
    return MH_DisableHook(target);
} 

MH_STATUS HookManager::EnableAllHooks() {
    return MH_EnableHook(MH_ALL_HOOKS);
}

