#pragma once

#include "../../ModuleBase.h"

class Watermark : public ModuleBase {
public:
	Watermark() : ModuleBase("Watermark", Category::Visual, 0x0, true) {}

	void OnImGuiRender() override;
};