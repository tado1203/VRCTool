#include "pch.h"

#include "Functions.h"

#include "Offsets.h"
#include "../Hook/Hooks/NotifyDetour.h"

VRC_SDKBase_VRCPlayerApi_o* Functions::Networking::GetLocalPlayer() {
	using FuncPtr = VRC_SDKBase_VRCPlayerApi_o*(*)();
	FuncPtr func = reinterpret_cast<FuncPtr>(Offsets::Networking::get_LocalPlayer);
	return func();
}

void Functions::Notification(const std::string& message) {
	if (stolenNotificationInstance == nullptr) {
		Logger::Log("[Notification] stolenNotificationInstance is null! Change your avatar");
		return;
	}

	// todo: implement
}