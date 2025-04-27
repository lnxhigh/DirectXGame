#pragma once

#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class Window;

class SwapChain
{
private:
	ComPtr<IDXGISwapChain> m_swap_chain = nullptr;

public:
	bool Init(Window* window, ID3D11Device* device);
	bool Resize(int width, int height);
	void Present();

	IDXGISwapChain* GetSwapChain() const { return m_swap_chain.Get(); }
};
