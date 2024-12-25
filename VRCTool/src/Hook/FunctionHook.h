#pragma once

class FunctionHook {
public:
    FunctionHook(void* target, void* detour);
    bool Create();
    bool Remove();

    template <typename T>
    T GetOriginal() {
        return reinterpret_cast<T>(original);
    }

private:
    void* target;
    void* detour;
    void* original;
};