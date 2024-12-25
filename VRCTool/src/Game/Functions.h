#pragma once

#include "pch.h"

namespace Functions {
	namespace Networking {
		VRC_SDKBase_VRCPlayerApi_o* GetLocalPlayer();
	}

	void Notification(const std::string& message);
}