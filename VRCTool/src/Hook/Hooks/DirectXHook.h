#pragma once

namespace DirectXHook {
	/**
	 * @brief Enables the DirectX hook for rendering.
	 */
	void Enable();

	/**
	 * @brief Disables the DirectX-related hook and shuts down the kiero library.
	 */
	void Disable();
}