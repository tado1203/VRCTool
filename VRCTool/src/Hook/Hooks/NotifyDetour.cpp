#include "pch.h"

#include "NotifyDetour.h"

#include "../../Utils/Utils.h"

void DetourNotify(________________________1654_o* instance, VRC_Localization_LocalizableString_o message) {
	stolenNotificationInstance = instance;
	stolenNotificationString = message;
	Logger::Log("Notify: message={}", Utils::ConvertSystemStringToStdString( message.fields._fallbackText));
	originalNotify(instance, message);
}