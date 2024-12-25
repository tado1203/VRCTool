#include "pch.h"

#include "FunctionHook.h"

#include "../../lib/minhook/MinHook.h"

FunctionHook::FunctionHook(void* target, void* detour) : target(target), detour(detour), original(nullptr) {}

bool FunctionHook::Create() {
    if (MH_CreateHook(target, detour, &original) != MH_OK) {
        return false;
    }
    return MH_EnableHook(target) == MH_OK;
}

bool FunctionHook::Remove() {
    if (MH_DisableHook(target) != MH_OK) {
        return false;
    }
    return MH_RemoveHook(target) == MH_OK;
}
