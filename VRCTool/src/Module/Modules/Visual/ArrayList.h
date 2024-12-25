#pragma once

#include "../../ModuleBase.h"

class ArrayList : public ModuleBase {
public:
	ArrayList() : ModuleBase("ArrayList", Category::Visual, 0x0, true) {}

	void OnImGuiRender() override;
};