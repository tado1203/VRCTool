#include "pch.h"

#include "HookManager.h"

#include "../../lib/minhook/MinHook.h"

void HookManager::Initialize() {
    if (!initialized) {
        MH_Initialize();
        initialized = true;
    }
}

void HookManager::Uninitialize() {
    if (initialized) {
        for (auto& hook : hooks) {
            hook.Remove();
        }
        hooks.clear();
        MH_Uninitialize();
        initialized = false;
    }
}

bool HookManager::AddHook(void* target, void* detour, void** original) {
    FunctionHook hook(target, detour);
    if (hook.Create()) {
		*original = hook.GetOriginal<void*>();
        hooks.push_back(hook);
        return true;
    }
    return false;
}
