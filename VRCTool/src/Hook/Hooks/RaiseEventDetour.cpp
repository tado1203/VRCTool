#include "pch.h"

#include "RaiseEventDetour.h"

bool DetourRaiseEvent(uint8_t eventCode, Il2CppObject* eventContent, ________________________1211_o* raiseEventOptions, ExitGames_Client_Photon_SendOptions_o sendOptions) {
	Logger::Log("RaiseEvent: eventCode={}", static_cast<int>(eventCode));
	return originalRaiseEvent(eventCode, eventContent, raiseEventOptions, sendOptions);
}