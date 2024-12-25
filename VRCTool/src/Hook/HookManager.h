#pragma once

#include <vector>

#include "FunctionHook.h"

class HookManager {
public:
    static void Initialize();
    static void Uninitialize();
    static bool AddHook(void* target, void* detour, void** original);

private:
    static inline bool initialized = false;
    static inline std::vector<FunctionHook> hooks;
};