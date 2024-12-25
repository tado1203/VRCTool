#include "pch.h"

#include "console.h"

void Console::Setup() {
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	SetConsoleTitleA("VRCTool");

	FILE* fpOut;
	FILE* fpErr;
	freopen_s(&fpOut, "CONOUT$", "w", stdout);  // Redirect stdout
	freopen_s(&fpErr, "CONOUT$", "w", stderr); // Redirect stderr
}

void Console::Cleanup() {
	HWND consoleWindow = GetConsoleWindow();
	FreeConsole();
	if (consoleWindow) {
		PostMessageA(consoleWindow, WM_CLOSE, 0, 0);
	}
}