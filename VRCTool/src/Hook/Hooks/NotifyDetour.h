#pragma once

#include "pch.h"

using NotifyFunc = void(*)(void* ________________________1654_o, VRC_Localization_LocalizableString_o message);

inline NotifyFunc originalNotify = nullptr;

inline VRC_Localization_LocalizableString_o stolenNotificationString;
inline ________________________1654_o* stolenNotificationInstance = nullptr;

void DetourNotify(________________________1654_o* instance, VRC_Localization_LocalizableString_o message);