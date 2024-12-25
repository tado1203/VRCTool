#include "pch.h"

#include "utils.h"

std::string Utils::ConvertSystemStringToStdString(const System_String_o* systemString) {
	if (systemString == nullptr || systemString->fields._stringLength <= 0)
		return "";

	int32_t length = systemString->fields._stringLength;
	const uint16_t* charPointer = &systemString->fields._firstChar;

	std::string utf8Result;
	utf8Result.reserve(length); // Reserve approximate size to minimize reallocations

    for (int32_t i = 0; i < length; ++i) {
        uint16_t codeUnit = charPointer[i];
 
        if (codeUnit <= 0x7F) {
            // 1-byte UTF-8 (ASCII)
            utf8Result.push_back(static_cast<char>(codeUnit));
        }
        else if (codeUnit <= 0x7FF) {
            // 2-byte UTF-8
            utf8Result.push_back(static_cast<char>(0xC0 | (codeUnit >> 6)));
            utf8Result.push_back(static_cast<char>(0x80 | (codeUnit & 0x3F)));
        }
        else {
            // 3-byte UTF-8
            utf8Result.push_back(static_cast<char>(0xE0 | (codeUnit >> 12)));
            utf8Result.push_back(static_cast<char>(0x80 | ((codeUnit >> 6) & 0x3F)));
            utf8Result.push_back(static_cast<char>(0x80 | (codeUnit & 0x3F)));
        }
    }

    return utf8Result;
}

System_String_o Utils::ConvertStdStringToSystemString(const std::string& stdString) {
    System_String_o systemString = {};

    if (stdString.empty())
        return systemString;

    systemString.fields._stringLength = static_cast<int32_t>(stdString.length());

    // Allocate memory for the characters
    uint16_t* charPointer = new uint16_t[systemString.fields._stringLength];
    systemString.fields._firstChar = *charPointer;

    for (size_t i = 0; i < stdString.length(); ++i) {
        charPointer[i] = static_cast<uint16_t>(stdString[i]);
    }

    return systemString;
}