#include "pch.h"

#include "DirectXHook.h"

#include <d3d11.h>
#include <dxgi.h>

#include "../../../lib/imgui/backends/imgui_impl_dx11.h"
#include "../../../lib/imgui/backends/imgui_impl_win32.h"
#include "../../../lib/kiero/kiero.h"

#include "WndProcHook.h"
#include "../../Module/ModuleManager.h"
#include "../../UI/FontManager.h"

using PresentFunc = HRESULT(__stdcall*)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags);
using ResizeBuffersFunc = HRESULT(_stdcall*)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);

ID3D11Device* device = nullptr;
ID3D11DeviceContext* context = nullptr;
ID3D11RenderTargetView* rtView = nullptr;
PresentFunc originalPresent = nullptr;

ResizeBuffersFunc originalResizeBuffers = nullptr;

/**
 * @brief Sets up resources for rendering.
 *
 * @param swapChain The IDXGISwapChain used to retrieve the Direct3D device.
 * @return true if initialization succeeds, false otherwise.
 */
bool Initialize(IDXGISwapChain* swapChain) {
	if (FAILED(swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device)))) {
		return false;
	}

	device->GetImmediateContext(&context);

	DXGI_SWAP_CHAIN_DESC desc;
	swapChain->GetDesc(&desc);

	ID3D11Texture2D* backBuffer = nullptr;
	if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)))) {
		return false;
	}

	if (FAILED(device->CreateRenderTargetView(backBuffer, NULL, &rtView))) {
		backBuffer->Release();
		return false;
	}

	backBuffer->Release();

	WndProcHook::Enable(desc.OutputWindow);
	ImGui::CreateContext();
	ImGui_ImplDX11_Init(device, context);
	ImGui_ImplWin32_Init(desc.OutputWindow);

	FontManager::LoadFonts();

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 10.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowTitleAlign = ImVec2(0.02f, 0.5f);
	style.FrameRounding = 2.5f;
	style.Colors[ImGuiCol_WindowShadow] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

	SetForegroundWindow(desc.OutputWindow);

	return true;
}

/**
 * @brief Renders the ImGui frame.
 *
 * This function sets up the ImGui frame for rendering, processes any modules that need to render their ImGui content.
 */
void RenderImGuiFrame() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ModuleManager::OnImGuiRender();

	ImGui::Render();

	context->OMSetRenderTargets(1, &rtView, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

HRESULT __stdcall HookPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
	static bool initialized = false;

	if (!initialized) {
		if (!Initialize(swapChain)) {
			return originalPresent(swapChain, syncInterval, flags); // Return early if initialization fails
		}
		initialized = true;
	}

	RenderImGuiFrame();

	return originalPresent(swapChain, syncInterval, flags);
}

/**
 * @brief Hooks the ResizeBuffers function to handle resizing of swap chain buffers and the render target view.
 */
HRESULT HookResizeBuffers(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	if (rtView != nullptr) {
		context->OMSetRenderTargets(0, 0, 0);
		rtView->Release();
		rtView = nullptr;  // Nullify to avoid dangling pointer
	}

	HRESULT hr = originalResizeBuffers(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
	if (FAILED(hr))
		return hr;

	ID3D11Texture2D* backBuffer = nullptr;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	if (FAILED(hr) || backBuffer == nullptr)
		return E_FAIL;

	hr = device->CreateRenderTargetView(backBuffer, NULL, &rtView);
	backBuffer->Release();
	if (FAILED(hr))
		return hr;

	context->OMSetRenderTargets(1, &rtView, NULL);

	D3D11_VIEWPORT vp = {};
	vp.Width = static_cast<FLOAT>(width);
	vp.Height = static_cast<FLOAT>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);

	return hr;
}

void DirectXHook::Enable() {
	if (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success)
		return;
	if (kiero::bind(8, reinterpret_cast<void**>(&originalPresent), HookPresent) == kiero::Status::Success)
		Logger::Log("[DirectXHook] Hooked IDXGISwapChain::Present");
	if (kiero::bind(13, reinterpret_cast<void**>(&originalResizeBuffers), HookResizeBuffers) == kiero::Status::Success)
		Logger::Log("[DirectXHook] Hooked IDXGISwapChain::ResizeBuffers");
}

void DirectXHook::Disable() {
	kiero::shutdown();
	WndProcHook::Disable();
}