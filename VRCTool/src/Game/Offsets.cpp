#include "pch.h"

#include "Offsets.h"

#include "PatternScanner.h"

void Offsets::FindPatterns() {
	HMODULE hModule = GetModuleHandleA("GameAssembly.dll");

	if (hModule == nullptr) {
		Logger::Log("Failed to get GameAssembly.dll module handle");
		return;
	}

	Networking::get_LocalPlayer = PatternScanner::GetCallTargetAddress(hModule, "Getter for Networking.LocalPlayer", "E8 ? ? ? ? 48 3B F8 75 ? C6 43");
	PhotonNetwork::RaiseEvent = PatternScanner::FindPattern(hModule, "PhotonNetwork.RaiseEvent()", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 88 4C 24");
	Notify = PatternScanner::FindPattern(hModule, "Notification Shit", "48 89 5C 24 ? 57 48 83 EC 60 80 3D ? ? ? ? ? 48 8B FA 48 8B D9 75 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? F0 83 0C 24 00 48 8D 0D ? ? ? ? E8 ? ? ? ? F0 83 0C 24 00 C6 05 ? ? ? ? ? 48 8B 05");
}