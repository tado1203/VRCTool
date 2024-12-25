#include "pch.h"

#include "PatternScanner.h"

#include <Psapi.h>

// helper
static std::vector<uint8_t> ConvertPatternToBytes(const std::string& pattern) {
    std::vector<uint8_t> bytes;
    std::stringstream stream(pattern);
    std::string byte;
    while (stream >> byte) {
        if (byte == "?")
            bytes.emplace_back(0x00);
        else {
            uint8_t value = static_cast<uint8_t>(std::stoi(byte, nullptr, 16));
            bytes.emplace_back(value);
        }
    }
    return bytes;
}

static std::vector<size_t> BuildGoodSuffixShift(const std::vector<uint8_t>& pattern) {
    size_t patternLength = pattern.size();
    std::vector<size_t> shift(patternLength + 1, patternLength);
    std::vector<size_t> borderPos(patternLength + 1, 0);

    size_t i = patternLength, j = patternLength + 1;
    borderPos[i] = j;

    while (i > 0) {
        while (j <= patternLength && pattern[i - 1] != pattern[j - 1]) {
            if (shift[j] == patternLength) {
                shift[j] = j - i;
            }
            j = borderPos[j];
        }
        --i;
        --j;
        borderPos[i] = j;
    }

    j = borderPos[0];
    for (i = 0; i <= patternLength; ++i) {
        if (shift[i] == patternLength) {
            shift[i] = j;
        }
        if (i == j) {
            j = borderPos[j];
        }
    }

    return shift;
}

// uses Boyer-Moore with Good Suffix Rule
uintptr_t PatternScanner::FindPattern(const HMODULE& hModule, const std::string& functionName, const std::string& pattern) {
    MODULEINFO moduleInfo = {};
    if (!K32GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(moduleInfo))) {
        Logger::Log("[PatternScanner] Failed to get module information.");
        return 0;
    }

    uint8_t* baseAddress = reinterpret_cast<uint8_t*>(moduleInfo.lpBaseOfDll);
    size_t moduleSize = moduleInfo.SizeOfImage;

    std::vector<uint8_t> patternBytes = ConvertPatternToBytes(pattern);
    size_t patternLength = patternBytes.size();

    if (patternLength == 0) {
        Logger::Log("[PatternScanner] Pattern length is 0.");
        return 0;
    }

    // Build the bad character shift table
    std::unordered_map<uint8_t, size_t> badCharacterShift;
    for (size_t i = 0; i < patternLength - 1; ++i) {
        badCharacterShift[patternBytes[i]] = patternLength - i - 1;
    }

    // Build the good suffix shift table
    std::vector<size_t> goodSuffixShift = BuildGoodSuffixShift(patternBytes);

    size_t i = 0;
    while (i <= moduleSize - patternLength) {
        size_t j = patternLength - 1;
        while ((j == std::string::npos || j >= 0) && (baseAddress[i + j] == patternBytes[j] || patternBytes[j] == 0x00)) {
            if (j == 0) {
                Logger::Log("[PatternScanner] {}: Relative offset from module base: 0x{:X}", functionName, reinterpret_cast<uintptr_t>(&baseAddress[i]));
                return reinterpret_cast<uintptr_t>(&baseAddress[i]);
            }
            --j;
        }

        uint8_t badChar = baseAddress[i + patternLength - 1];
        auto shift = badCharacterShift.find(badChar);
        size_t badCharShift = (shift != badCharacterShift.end()) ? shift->second : patternLength;
        size_t goodSuffixShiftValue = goodSuffixShift[j + 1];

        i += std::max(badCharShift, goodSuffixShiftValue);
    }

    Logger::Log("[PatternScanner] {}: Pattern not found", functionName);
    return 0;
}

uintptr_t PatternScanner::GetCallTargetAddress(const HMODULE& hModule, const std::string& functionName, const std::string& pattern) {
    uintptr_t patternAddress = FindPattern(hModule, functionName, pattern);
    if (patternAddress == 0) {
        return 0;
    }

    uint8_t* callAddress = reinterpret_cast<uint8_t*>(patternAddress);
    int32_t relativeOffset = *reinterpret_cast<int32_t*>(callAddress + 1); // 1 to get 4 bytes after E8

    uintptr_t absoluteAddress = patternAddress + 5 + relativeOffset;

    uintptr_t moduleBaseAddress = reinterpret_cast<uintptr_t>(hModule);
    uintptr_t relativeAddressFromModule = absoluteAddress - moduleBaseAddress;

    Logger::Log("[PatternScanner] {}: Relative offset from E8 (Module Base): 0x{:X}", functionName, relativeAddressFromModule);

    return absoluteAddress;
}