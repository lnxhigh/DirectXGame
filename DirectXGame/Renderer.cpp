#include <iostream>
#include <assert.h>
#include <wrl/client.h>
#include "Renderer.h"

using Microsoft::WRL::ComPtr;

Renderer::Renderer(HWND hwnd)
{
    InitWindowInfo(hwnd);
    InitDevice();
    InitSwapChain();
    InitRenderTarget();
}

Renderer::~Renderer()
{
    
}

void Renderer::InitWindowInfo(HWND hwnd)
{
    m_hwnd = hwnd;

    RECT rect;
    GetClientRect(hwnd, &rect);
    m_width = rect.right - rect.left;
    m_height = rect.bottom - rect.top;
}

void Renderer::InitDevice()
{
    D3D_FEATURE_LEVEL feature_level;

    HRESULT hr = D3D11CreateDevice(
        0, // default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        0, // no software device
        0,
        0, 0, // default feature level array
        D3D11_SDK_VERSION,
        m_device.GetAddressOf(),
        &feature_level,
        m_context.GetAddressOf()
    );

    if (FAILED(hr))
    {
        std::cerr << "Error: Failed to create D3D11 device" << std::endl;
        exit(-1);
    }
    
    if (feature_level != D3D_FEATURE_LEVEL_11_0)
    {
        std::cerr << "Error: Direct3D Feature Level 11 unsupported" << std::endl;
        exit(-1);
    }

}

void Renderer::InitSwapChain()
{
    DXGI_SWAP_CHAIN_DESC desc = { };

    desc.BufferDesc.Width = m_width;
    desc.BufferDesc.Height = m_height;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = 1;
    desc.OutputWindow = m_hwnd;
    desc.Windowed = true;
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    desc.Flags = 0;

    // Get the IDXGIFactory interface

    ComPtr<IDXGIDevice> dxgi_device = nullptr;
    ComPtr<IDXGIAdapter> dxgi_adapter = nullptr;
    ComPtr<IDXGIFactory> dxgi_factory = nullptr;

    m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)dxgi_device.GetAddressOf());
    dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)dxgi_adapter.GetAddressOf());
    dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)dxgi_factory.GetAddressOf());
    
    // Create the swap chain

    HRESULT hr = dxgi_factory->CreateSwapChain(m_device.Get(), &desc, m_swap_chain.GetAddressOf());

    if (FAILED(hr)) {
        std::cerr << "Error: Failed to create SwapChain" << std::endl;
        exit(-1);
    }
}

void Renderer::InitRenderTarget()
{
    ComPtr<ID3D11Texture2D> buffer = nullptr;
    m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) buffer.GetAddressOf());
    assert(buffer);

    HRESULT hr = m_device->CreateRenderTargetView(
        buffer.Get(), nullptr, 
        m_render_target_view.GetAddressOf()
    );

    if (FAILED(hr)) {
        std::cerr << "Error: Failed to create RenderTargetView" << std::endl;
        exit(-1);
    }
}

void Renderer::InitDepthStencilBuffer()
{
    D3D11_TEXTURE2D_DESC desc = { };

    desc.Width = m_width;
    desc.Height = m_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    desc.SampleDesc.Count = 1; // No Multisampling
    desc.SampleDesc.Quality = 0;

    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    
    // Bind Depth Stencil Buffer

    ComPtr<ID3D11Texture2D> buffer;
    ComPtr<ID3D11DepthStencilView> view;

    m_device->CreateTexture2D(&desc, 0, buffer.GetAddressOf());
    assert(buffer);

    HRESULT hr = m_device->CreateDepthStencilView(buffer.Get(), 0, view.GetAddressOf());
    
    if (FAILED(hr))
    {
        std::cerr << "Error: Failed to create DepthStencilView" << std::endl;
        exit(-1);
    }
}

void Renderer::InitViewport()
{
    D3D11_VIEWPORT viewport = { };

    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    viewport.Width = (float) m_width;
    viewport.Height = (float) m_height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    m_context->RSSetViewports(1, &viewport);
}

void Renderer::Render()
{
    float color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    m_context->ClearRenderTargetView(m_render_target_view.Get(), color);
    m_swap_chain->Present(1, 0);
}
