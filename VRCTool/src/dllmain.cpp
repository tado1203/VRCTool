#include "pch.h"

#include <thread>

#include "Utils/Console.h"
#include "Game/Offsets.h"
#include "Hook/HookManager.h"
#include "Module/ModuleManager.h"
#include "Hook/Hooks/DirectXHook.h"
#include "Globals.h"

// hooks
#include "Hook/Hooks/RaiseEventDetour.h"
#include "Hook/Hooks/NotifyDetour.h"

DWORD WINAPI ThreadProc(LPVOID lpParam) {
	if (!std::filesystem::exists("VRCTool")) {
		std::filesystem::create_directory("VRCTool");
	}

	Console::Setup();

	std::cout << R"(
 /$$    /$$ /$$$$$$$   /$$$$$$  /$$$$$$$$ /$$$$$$   /$$$$$$  /$$      
| $$   | $$| $$__  $$ /$$__  $$|__  $$__//$$__  $$ /$$__  $$| $$      
| $$   | $$| $$  \ $$| $$  \__/   | $$  | $$  \ $$| $$  \ $$| $$      
|  $$ / $$/| $$$$$$$/| $$         | $$  | $$  | $$| $$  | $$| $$      
 \  $$ $$/ | $$__  $$| $$         | $$  | $$  | $$| $$  | $$| $$      
  \  $$$/  | $$  \ $$| $$    $$   | $$  | $$  | $$| $$  | $$| $$      
   \  $/   | $$  | $$|  $$$$$$/   | $$  |  $$$$$$/|  $$$$$$/| $$$$$$$$
    \_/    |__/  |__/ \______/    |__/   \______/  \______/ |________/
)" << '\n';

	// initialize IL2CPP_Resolver
	IL2CPP::Initialize();

	IL2CPP::Callback::Initialize();
	IL2CPP::Callback::OnUpdate::Add(ModuleManager::OnUpdate);

	Offsets::FindPatterns();

	HookManager::Initialize();
	if (HookManager::AddHook(reinterpret_cast<void*>(Offsets::PhotonNetwork::RaiseEvent), reinterpret_cast<void*>(&DetourRaiseEvent), reinterpret_cast<void**>(&originalRaiseEvent)))
		Logger::Log("[HookManager] Hooked RaiseEvent");
	if (HookManager::AddHook(reinterpret_cast<void*>(Offsets::Notify), reinterpret_cast<void*>(&DetourNotify), reinterpret_cast<void**>(&originalNotify)))
		Logger::Log("[HookManager] Hooked Notification Shit");

	ModuleManager::SetupModules();

	DirectXHook::Enable();

	while (!Globals::shouldUnload)
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	Logger::Log("[DllMain] Unloading...");

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 0);

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, ThreadProc, hModule, 0, NULL);
		break;
	case DLL_PROCESS_DETACH:
		DirectXHook::Disable();
		HookManager::Uninitialize();
		Console::Cleanup();
		break;
	}
	return TRUE;
}