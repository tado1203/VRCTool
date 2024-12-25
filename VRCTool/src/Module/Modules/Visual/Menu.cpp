#include "pch.h"

#include "Menu.h"

#include "../../ModuleManager.h"
#include "../../../Hook/Hooks/WndProcHook.h"
#include "../../../UI/FontsData/IconsFontAwesome6.h"
#include "../../../Globals.h"

static void DrawModules(int currentCategoryIndex) {
	for (const auto module : ModuleManager::modules) {
		if (static_cast<int>(module->category) != currentCategoryIndex)
			continue;
		
		if (ImGui::CollapsingHeader(module->name.c_str())) {
			ImGui::PushID((module->name + "_isEnabled").c_str());
			ImGui::Checkbox("Enabled", &module->isEnabled);
			ImGui::PopID();

			module->OnMenu();
		}
	}
}

void Menu::OnImGuiRender() {
	if (isEnabled) {
		constexpr int categoryCount = 2;
		const std::array<std::string, 2> tabBarItems = { ICON_FA_EYE" Visual", ICON_FA_CODE" Udon" };

		ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_Once);

		ImGui::Begin("VRCTool", NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
 

		ImGui::BeginTabBar("Categories");

		for (int i = 0; i < categoryCount; ++i) {
			if (ImGui::BeginTabItem(tabBarItems[i].c_str())) {

				DrawModules(i);

				ImGui::EndTabItem();
			}
		}

		ImGui::EndTabBar();
		
		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowContentRegionMax().x - ImGui::CalcTextSize(ICON_FA_RIGHT_FROM_BRACKET).x - ImGui::GetStyle().FramePadding.x * 2, ImGui::GetWindowContentRegionMax().y - ImGui::GetFrameHeightWithSpacing()));
		if (ImGui::Button(ICON_FA_RIGHT_FROM_BRACKET))
			Globals::shouldUnload = true;

		ImGui::End();
	}
}

void Menu::OnEnable() {
	ImGui::GetIO().MouseDrawCursor = true;
	WndProcHook::shouldBlockInput = true;
}

void Menu::OnDisable() {
	ImGui::GetIO().MouseDrawCursor = false;
	WndProcHook::shouldBlockInput = false;
}