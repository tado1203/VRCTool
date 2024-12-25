#include "pch.h"

#include "ModuleBase.h"

ModuleBase::ModuleBase(const std::string& name, Category category, int keyBind, bool isEnabled)
	: name(name), category(category), keyBind(keyBind), isEnabled(isEnabled) { }

void ModuleBase::Toggle() {
	isEnabled = !isEnabled;
	if (isEnabled)
		OnEnable();
	else
		OnDisable();
}