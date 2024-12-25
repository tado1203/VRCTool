#pragma once

#include "pch.h"

namespace WndProcHook {
	/**
	 * @brief Enables the custom window procedure hook.
	 */
	void Enable(HWND hWnd);

	/**
	 * @brief Disables the custom window procedure hook and restores the original procedure.
	 */
	void Disable();

	/**
	 * @brief Array to keep track of the current state of keyboard and mouse keys.
	 *
	 * Each index corresponds to a virtual-key code, with `true` indicating the key is pressed
	 * and `false` indicating it is released.
	 */
	extern std::array<bool, 256> keyListener;

	/**
	 * @brief Flag indicating whether input should be blocked.
	 *
	 * If true, mouse and keyboard input events are blocked.
	 */
	extern bool shouldBlockInput;
}