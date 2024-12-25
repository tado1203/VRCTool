#include "pch.h"

#include "WndProcHook.h"

#include "../../../lib/imgui/backends/imgui_impl_win32.h"

#include "../../Module/ModuleManager.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using WndProcFunc = LRESULT(__stdcall*)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::array<bool, 256> WndProcHook::keyListener;
bool WndProcHook::shouldBlockInput = false;

WndProcFunc originalWndProcFunc = nullptr;
HWND handleWindow;

/**
 * @brief Custom window procedure hook to handle keyboard and mouse inputs.
 */
LRESULT __stdcall HookWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	auto SetKeyState = [](int key, bool state) {
		WndProcHook::keyListener[key] = state;
	};

	ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

	bool isMouseOrKeyboardInput = false;

	switch (msg) {
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		SetKeyState(VK_LBUTTON, msg == WM_LBUTTONDOWN);
		isMouseOrKeyboardInput = true;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		SetKeyState(VK_RBUTTON, msg == WM_RBUTTONDOWN);
		isMouseOrKeyboardInput = true;
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		SetKeyState(VK_MBUTTON, msg == WM_MBUTTONDOWN);
		isMouseOrKeyboardInput = true;
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP: {
		int key = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? VK_XBUTTON1 : VK_XBUTTON2;
		SetKeyState(key, msg == WM_XBUTTONDOWN);
		isMouseOrKeyboardInput = true;
		break;
	}
	case WM_KEYDOWN:
	case WM_KEYUP:
		SetKeyState(static_cast<int>(wParam), msg == WM_KEYDOWN);
		isMouseOrKeyboardInput = true;
		break;
	}

	for (auto module : ModuleManager::modules) {
		if (module->keyBind == static_cast<int>(wParam) && msg == WM_KEYDOWN)
			module->Toggle();
	}

	if (isMouseOrKeyboardInput && WndProcHook::shouldBlockInput)
		return false;

	return CallWindowProcA(reinterpret_cast<WNDPROC>(originalWndProcFunc), hWnd, msg, wParam, lParam);
}

void WndProcHook::Enable(HWND hWnd) {
	handleWindow = hWnd;
	originalWndProcFunc = (WndProcFunc)SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HookWndProc));
	SetWindowTextA(hWnd, "VRChat: Developer Edition"); // mocking
}

void WndProcHook::Disable() {
	SetWindowLongPtrA(handleWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(originalWndProcFunc));
	originalWndProcFunc = nullptr;
}