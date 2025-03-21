#include <iostream>
#include <assert.h>
#include "Renderer.h"

Renderer::Renderer(HWND hwnd)
{
    InitWindowInfo(hwnd);
    InitDevice();
    InitSwapChain();
    InitRenderTarget();
}

Renderer::~Renderer()
{
    if (m_render_target_view) m_render_target_view->Release();
    if (m_swap_chain) m_swap_chain->Release();
    if (m_context) m_context->Release();
    if (m_device) m_device->Release();
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
    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &m_device, &featureLevel, &m_context
    );

    if (FAILED(hr)) {
        std::cerr << "Failed to create D3D11 device!" << std::endl;
        exit(-1);
    }
}

void Renderer::InitSwapChain()
{
    DXGI_SWAP_CHAIN_DESC desc = { };
    desc.BufferCount = 2;
    desc.BufferDesc.Width = m_width;
    desc.BufferDesc.Height = m_height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = m_hwnd;
    desc.SampleDesc.Count = 1;
    desc.Windowed = TRUE;

    IDXGIFactory* factory = nullptr;
    CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    HRESULT hr = factory->CreateSwapChain(m_device, &desc, &m_swap_chain);
    factory->Release();

    if (FAILED(hr)) {
        std::cerr << "Error: Failed to create SwapChain" << std::endl;
        exit(-1);
    }
}

void Renderer::InitRenderTarget()
{
    ID3D11Texture2D* back_buffer = nullptr;
    m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back_buffer);
    
    assert(back_buffer);
    HRESULT hr = m_device->CreateRenderTargetView(back_buffer, nullptr, &m_render_target_view);
    back_buffer->Release();

    if (FAILED(hr)) {
        std::cerr << "Error: Failed to create RenderTargetView" << std::endl;
        exit(-1);
    }
}

void Renderer::InitDepthStencilBuffer()
{
    D3D11_TEXTURE2D_DESC desc;
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

    ID3D11Texture2D* buffer;
    m_device->CreateTexture2D(&desc, 0, &buffer);
    assert(buffer);

    HRESULT hr = m_device->CreateDepthStencilView(buffer, 0, &m_depth_stencil_view);
    buffer->Release();
    
    if (FAILED(hr))
    {
        std::cerr << "Error: Failed to create DepthStencilView" << std::endl;
        exit(-1);
    }
}

void Renderer::Render()
{
    float color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    m_context->ClearRenderTargetView(m_render_target_view, color);
    m_swap_chain->Present(1, 0);
}
