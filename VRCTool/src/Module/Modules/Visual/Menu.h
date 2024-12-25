#pragma once

#include "../../ModuleBase.h"

class Menu : public ModuleBase {
public:
	Menu() : ModuleBase("Menu", Category::Visual, VK_INSERT) {}

	void OnImGuiRender() override;
	void OnEnable() override;
	void OnDisable() override;
};