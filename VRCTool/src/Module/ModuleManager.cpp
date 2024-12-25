#include "pch.h"

#include "ModuleManager.h"

#include "Modules/Visual/Menu.h"
#include "Modules/Visual/Watermark.h"
#include "Modules/Visual/ArrayList.h"

void ModuleManager::SetupModules() {
	modules.emplace_back(new Menu());
	modules.emplace_back(new Watermark());
	modules.emplace_back(new ArrayList());
}

void ModuleManager::SortModules() {
	std::sort(modules.begin(), modules.end(), [](ModuleBase* a, ModuleBase* b) {
		return ImGui::CalcTextSize(a->name.c_str()).x > ImGui::CalcTextSize(b->name.c_str()).x;
	});
}

void ModuleManager::OnUpdate() {
	for (auto module : modules) {
		module->OnUpdate();
	}
}

void ModuleManager::OnImGuiRender() {
	for (auto module : modules) {
		module->OnImGuiRender();
	}
}