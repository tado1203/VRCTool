#pragma once

#include "pch.h"

using RaiseEventFunc = bool(*)(uint8_t eventCode, Il2CppObject* eventContent, ________________________1211_o* raiseEventOptions, ExitGames_Client_Photon_SendOptions_o sendOptions);

inline RaiseEventFunc originalRaiseEvent = nullptr;

bool DetourRaiseEvent(uint8_t eventCode, Il2CppObject* eventContent, ________________________1211_o* raiseEventOptions, ExitGames_Client_Photon_SendOptions_o sendOptions);