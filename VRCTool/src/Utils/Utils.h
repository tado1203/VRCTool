#pragma once

#include "pch.h"

namespace Utils {
	std::string ConvertSystemStringToStdString(const System_String_o* systemString);
	System_String_o ConvertStdStringToSystemString(const std::string& stdString);
}