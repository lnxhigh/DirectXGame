#pragma once
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class Window;

class FrameBuffer
{
public:
    ID3D11RenderTargetView* GetRTV() const { return m_rtv.Get(); }
    ID3D11RenderTargetView** GetRTVAddress() { return m_rtv.GetAddressOf(); }

    ID3D11DepthStencilView* GetDSV() const { return m_dsv.Get(); }
    ID3D11DepthStencilView** GetDSVAddress() { return m_dsv.GetAddressOf(); }

public:
    bool CreateRenderTarget(ID3D11Device* device, IDXGISwapChain* swap_chain);
    bool CreateDepthStencil(Window* window, ID3D11Device* device, IDXGISwapChain* swap_chain);

private:
    ComPtr<ID3D11RenderTargetView> m_rtv;
    ComPtr<ID3D11DepthStencilView> m_dsv;
};

