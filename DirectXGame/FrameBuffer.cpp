#include "FrameBuffer.h"
#include "Window.h"

bool FrameBuffer::CreateRenderTarget(ID3D11Device* device, IDXGISwapChain* swap_chain)
{
    // Get back buffer from swap chain

    ComPtr<ID3D11Texture2D> backBuffer = nullptr;
    swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());

    if (!backBuffer)
    {
        OutputDebugStringA("Error: Failed to get back buffer from swap chain\n");
        return false;
    }

    // Create render target view

    ComPtr<ID3D11RenderTargetView> view;

    HRESULT hr = device->CreateRenderTargetView(
        backBuffer.Get(), nullptr,
        view.GetAddressOf()
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create RenderTargetView\n");
        return false;
    }

    // Assign value

    m_rtv = view;

    return true;
}

bool FrameBuffer::CreateDepthStencil(Window* window, ID3D11Device* device, IDXGISwapChain* swap_chain)
{
    D3D11_TEXTURE2D_DESC desc = { };

    desc.Width = window->GetWidth();
    desc.Height = window->GetHeight();
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    desc.SampleDesc.Count = 1; // No Multisampling
    desc.SampleDesc.Quality = 0;

    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    // Create depth stencil buffer

    ComPtr<ID3D11Texture2D> buffer;
    device->CreateTexture2D(&desc, 0, buffer.GetAddressOf());

    if (!buffer)
    {
        OutputDebugStringA("Error: Failed to create Texture2D\n");
        return false;
    }

    // Create depth stencil view

    ComPtr<ID3D11DepthStencilView> view;
    HRESULT hr = device->CreateDepthStencilView(buffer.Get(), 0, view.GetAddressOf());

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create DepthStencilView\n");
        return false;
    }

    // Assign value

    m_dsv = view;

    return true;
}
