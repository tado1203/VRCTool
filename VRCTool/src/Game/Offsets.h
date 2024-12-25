#pragma once

#include "pch.h"

namespace Offsets {
	namespace Networking {
		inline uintptr_t get_LocalPlayer = 0;
	}

	namespace PhotonNetwork {
		inline uintptr_t RaiseEvent = 0;
	}

	inline uintptr_t Notify = 0;

	namespace Il2Cpp {
		inline uintptr_t il2cpp_thread_attach = 0;
		inline uintptr_t il2cpp_domain_get = 0;
		inline uintptr_t il2cpp_object_new = 0;
	}

	void FindPatterns();
}