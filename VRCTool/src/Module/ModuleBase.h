#pragma once

#include "pch.h"

enum class Category {
	Visual,
	Udon
};

/**
 * @class ModuleBase
 * @brief A base class for modules with common properties and functionality.
 */
class ModuleBase {
public:
	std::string name;
	Category category;
	int keyBind;
	bool isEnabled;

	ModuleBase(const std::string& name, Category category, int keyBind = 0x0, bool isEnabled = false);

	/**
	 * @brief Virtual method to be implemented by derived classes for updates.
	 *
	 * This method is called during each update cycle. Derived classes can implement
	 * specific behavior for the MonoBehaviour.Update() process.
	 */
	virtual void OnUpdate() {};

	virtual void OnImGuiRender() {};
	virtual void OnMenu() {};
	virtual void OnEnable() {};
	virtual void OnDisable() {};

	void Toggle();
};