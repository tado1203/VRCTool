#include "pch.h"

#include "ArrayList.h"

#include "../../ModuleManager.h"
#include "../../../UI/FontManager.h"
#include "../../../UI/FontsData/IconsFontAwesome6.h"
#include "../../../Utils/MathUtil.h"

void ArrayList::OnImGuiRender() {
	if (!isEnabled) return;

	static bool initialized = false;
	if (!initialized) {
		ModuleManager::SortModules();
		initialized = true;
	}

	const ImGuiIO& io = ImGui::GetIO();
	ImDrawList* drawList = ImGui::GetForegroundDrawList();

	constexpr ImVec2 padding(10.0f, 10.0f);
	constexpr float backgroundAlpha = 0.6f;
	constexpr float cornerRadius = 10.0f;
	const ImColor backgroundColor(0.0f, 0.0f, 0.0f, backgroundAlpha);
	const ImColor textColor(255, 255, 255);
	const ImColor iconColor(150, 150, 150);

	static std::unordered_map<ModuleBase*, float> animProgressMap;

	ImGui::PushFont(FontManager::robotoMedium);

	float yOffset = 20.0f;
	for (const auto& module : ModuleManager::modules) {
		// initialize
		float& animProgress = animProgressMap[module];
		if (animProgressMap.find(module) == animProgressMap.end())
			animProgress = 0.0f;

		animProgress = Math::SmoothExponential(animProgress, module->isEnabled ? 1.0f : 0.0f, io.DeltaTime * 15.0f);

		std::string name = module->name;
		std::string icon = " ";

		// Determine the icon based on category
		switch (module->category) {
		case Category::Visual:
			icon += ICON_FA_EYE;
			break;
		case Category::Udon:
			icon += ICON_FA_CODE;
			break;
		}

		// Calculate sizes and positions
		const ImVec2 nameSize = ImGui::CalcTextSize(name.c_str());
		const ImVec2 iconSize = ImGui::CalcTextSize(icon.c_str());
		const ImVec2 totalSize = ImVec2(nameSize.x + iconSize.x + padding.x * 2.0f, nameSize.y + padding.y * 2.0f);

		const float rectPosX = ImLerp(io.DisplaySize.x, io.DisplaySize.x - totalSize.x - padding.x, animProgress);
		const ImVec2 rectMinPos(rectPosX, yOffset);
		const ImVec2 rectMaxPos = rectMinPos + totalSize;

		// Draw background rectangle
		drawList->AddRectFilled(rectMinPos, rectMaxPos, backgroundColor, cornerRadius);

		// Draw text and icon
		const ImVec2 textPos = rectMinPos + padding;
		drawList->AddText(textPos, textColor, name.c_str());
		drawList->AddText(ImVec2(textPos.x + nameSize.x, textPos.y), iconColor, icon.c_str());

		// Adjust yOffset only if the module is enabled
		yOffset += (totalSize.y + padding.y) * animProgress;
	}

	ImGui::PopFont();
}