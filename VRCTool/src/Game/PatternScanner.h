#pragma once

#include "pch.h"

namespace PatternScanner {
	uintptr_t FindPattern(const HMODULE& hModule, const std::string& functionName, const std::string& pattern);
	uintptr_t GetCallTargetAddress(const HMODULE& hModule, const std::string& functionName, const std::string& pattern);
}