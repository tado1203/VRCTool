#pragma once

#include "pch.h"

#include "ModuleBase.h"

namespace ModuleManager {
	/// The vector that stores the instances of all the modules.
	inline std::vector<ModuleBase*> modules;

	/**
	 * @brief Adds the modules to the `modules` vector.
	 */
	void SetupModules();

	/**
	 * @brief Sorts the modules in the 'modules' vector based on the width of their names, in descending order.
	 */
	void SortModules();

	/**
	 * @brief Calls the `OnUpdate` method for all the modules in the `modules` vector.
	 */
	void OnUpdate();

	/**
	 * @brief Calls the `OnImGuiRender` method for all the modules in the `modules` vector.
	 */
	void OnImGuiRender();
}