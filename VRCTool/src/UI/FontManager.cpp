#include "pch.h"

#include "FontManager.h"

#include "FontsData/RobotoRegular.h"
#include "FontsData/RobotoMedium.h"
#include "FontsData/fontawesome.h"
#include "FontsData/IconsFontAwesome6.h"

ImFont* FontManager::robotoRegular = nullptr;
ImFont* FontManager::robotoMedium = nullptr;

void FontManager::LoadFonts() {
	const ImGuiIO& io = ImGui::GetIO();
	static const ImWchar iconRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

	robotoRegular = io.Fonts->AddFontFromMemoryCompressedTTF(robotoRegular_compressed_data, robotoRegular_compressed_size, 16.0f);
	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphMinAdvanceX = 16.0f;
	config.GlyphOffset = ImVec2(0.0f, 1.0f);
	robotoRegular = io.Fonts->AddFontFromMemoryCompressedTTF(fontawesome_compressed_data, fontawesome_compressed_size, 16.0f, &config, iconRanges);

	robotoMedium = io.Fonts->AddFontFromMemoryCompressedTTF(robotoMedium_compressed_data, robotoMedium_compressed_size, 20.0f);
	ImFontConfig config2;
	config2.MergeMode = true;
	config2.GlyphMinAdvanceX = 20.0f;
	config2.GlyphOffset = ImVec2(0.0f, 1.25f);
	robotoMedium = io.Fonts->AddFontFromMemoryCompressedTTF(fontawesome_compressed_data, fontawesome_compressed_size, 20.0f, &config2, iconRanges);
}