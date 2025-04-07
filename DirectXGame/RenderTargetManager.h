#pragma once

#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class Window;

class RenderTargetManager
{
public:
    ID3D11RenderTargetView* GetRTV() const { return m_rtv.Get(); }
    ID3D11DepthStencilView* GetDSV() const { return m_dsv.Get(); }

public:
    bool CreateRenderTarget(ID3D11Device* device, IDXGISwapChain* swap_chain);
    bool CreateDepthStencil(Window* window, ID3D11Device* device, IDXGISwapChain* swap_chain);

private:
    ComPtr<ID3D11RenderTargetView> m_rtv;
    ComPtr<ID3D11DepthStencilView> m_dsv;
};
