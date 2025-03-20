#include <iostream>
#include <assert.h>
#include "Renderer.h"

Renderer::Renderer(HWND hwnd)
{
    InitDevice();
    InitSwapChain(hwnd);
    InitRenderTarget();
}

Renderer::~Renderer()
{
    if (m_render_target_view) m_render_target_view->Release();
    if (m_swap_chain) m_swap_chain->Release();
    if (m_context) m_context->Release();
    if (m_device) m_device->Release();
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

void Renderer::InitSwapChain(HWND hwnd)
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    UINT width = rect.right - rect.left;
    UINT height = rect.bottom - rect.top;

    DXGI_SWAP_CHAIN_DESC desc = { };
    desc.BufferCount = 1;
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hwnd;
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
    ID3D11Texture2D* backBuffer = nullptr;
    m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    
    assert(backBuffer);
    HRESULT hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_render_target_view);
    backBuffer->Release();

    if (FAILED(hr)) {
        std::cerr << "Error: Failed to create RenderTargetView" << std::endl;
        exit(-1);
    }
}

void Renderer::Render()
{
    float color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    m_context->ClearRenderTargetView(m_render_target_view, color);
    m_swap_chain->Present(1, 0);
}
