#include "SwapChain.h"
#include "Window.h"

bool SwapChain::Init(Window* window, ID3D11Device* device)
{
    DXGI_SWAP_CHAIN_DESC desc = { };

    desc.BufferDesc.Width = window->GetWidth();
    desc.BufferDesc.Height = window->GetHeight();
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;

    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = 1;
    desc.OutputWindow = window->GetHwnd();
    desc.Windowed = true;
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    desc.Flags = 0;

    // Get the IDXGIFactory interface

    ComPtr<IDXGIDevice> dxgi_device = nullptr;
    ComPtr<IDXGIAdapter> dxgi_adapter = nullptr;
    ComPtr<IDXGIFactory> dxgi_factory = nullptr;

    device->QueryInterface(__uuidof(IDXGIDevice), (void**)dxgi_device.GetAddressOf());
    dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)dxgi_adapter.GetAddressOf());
    dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)dxgi_factory.GetAddressOf());

    // Create the swap chain

    HRESULT hr = dxgi_factory->CreateSwapChain(device, &desc, m_swap_chain.GetAddressOf());

    if (FAILED(hr)) {
        OutputDebugStringA("Error: Failed to create a SwapChain\n");
        return false;
    }

    return true;
}

bool SwapChain::Resize(int width, int height)
{
    HRESULT hr = m_swap_chain.Get()->ResizeBuffers(0, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
    if (FAILED(hr)) {
        OutputDebugStringA("Error: Failed to resize swap chain buffer\n");
        return false;
    }

    return true;
}

void SwapChain::Present()
{
    m_swap_chain.Get()->Present(1, 0);
}