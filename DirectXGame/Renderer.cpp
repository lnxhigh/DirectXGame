#include "Renderer.h"
#include "Vertex.h"
#include <iostream>
#include <assert.h>
#include <fstream>

using Microsoft::WRL::ComPtr;

Renderer::Renderer(HWND hwnd)
{
    InitWindowInfo(hwnd);
    InitDevice();
    InitSwapChain();
    InitRenderTarget();
    InitDepthStencilBuffer();
    InitViewport();
    InitShader(L"VertexShader.hlsl", L"PixelShader.hlsl");
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

    m_viewport = viewport;
    m_context->RSSetViewports(1, &viewport);
}

bool Renderer::InitShader(const wchar_t* vs_filename, const wchar_t* ps_filename)
{
    ComPtr<ID3DBlob> vs_blob = nullptr;
    ComPtr<ID3DBlob> ps_blob = nullptr;
    ComPtr<ID3DBlob> err_blob = nullptr;

    // Compile Vertex Shader

    HRESULT hr = D3DCompileFromFile(
        vs_filename,
        nullptr, 
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", "vs_5_0",
        0, 0,
        &vs_blob, &err_blob
    );

    if (FAILED(hr)) {
        if (err_blob)
        {
            OutputDebugStringA("Error: Failed to compile a vertex shader from the file.\n");
            OutputDebugStringA((char*)err_blob->GetBufferPointer());
        }
        return false;
    }

    // Compile Pixel Shader

    hr = D3DCompileFromFile(
        ps_filename,
        nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", "ps_5_0",
        0, 0,
        &ps_blob, &err_blob
    );

    if (FAILED(hr)) {
        if (err_blob)
        {
            OutputDebugStringA("Error: Failed to compile a pixel shader from the file.\n");
            OutputDebugStringA((char*)err_blob->GetBufferPointer());
        }
        return false;
    }

    // Create Vertex Shader

    hr = m_device->CreateVertexShader(
        vs_blob->GetBufferPointer(),
        vs_blob->GetBufferSize(),
        nullptr,
        &m_vertex_shader
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create a vertex shader.\n");
        return false;
    }

    hr = m_device->CreatePixelShader(
        ps_blob->GetBufferPointer(),
        ps_blob->GetBufferSize(),
        nullptr,
        &m_pixel_shader
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create a pixel shader.\n");
        return false;
    }

    m_vs_blob = vs_blob;
    m_ps_blob = ps_blob;

    return true;
}

bool Renderer::LoadVertex(void* vertices, unsigned int size_vertex, unsigned int size_list,
    void* shader_byte_code, unsigned int size_byte_code)
{
    D3D11_BUFFER_DESC desc = { };
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = size_vertex * size_list;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = { };
    init_data.pSysMem = vertices;

    ComPtr<ID3D11Buffer> buffer = nullptr;
    HRESULT hr_buffer = m_device->CreateBuffer(&desc, &init_data, buffer.GetAddressOf());
    
    if (FAILED(hr_buffer))
    {
        return false;
    }

    // Create the vertex input layout
    // SemanticName - SemanticIndex - Format - InputSlot -  AlignedByteOffset - 
    // InputSlotClass - InstanceDataStepRate

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    ComPtr<ID3D11InputLayout> input_layout = nullptr;
    HRESULT hr_layout = m_device->CreateInputLayout(layout, ARRAYSIZE(layout),
        shader_byte_code, size_byte_code, input_layout.GetAddressOf());
    
    if (FAILED(hr_layout)) 
    {
        return false;
    }

    m_vertex_buffer = buffer;
    m_input_layout = input_layout;

    return true;
}

void Renderer::Render()
{
    // Set Render Target
    m_context->OMSetRenderTargets(
        1,
        m_render_target_view.GetAddressOf(),
        m_depth_stencil_view.Get()
    );

    // Clear 
    float color[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    m_context->ClearRenderTargetView(m_render_target_view.Get(), color);
    m_context->ClearDepthStencilView(m_depth_stencil_view.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    // Set viewport
    m_context->RSSetViewports(1, &m_viewport);

    // Set shader and input layout
    m_context->IASetInputLayout(m_input_layout.Get());
    m_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
    m_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);

    // Set primitive topology
    m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Load vertex
    Vertex triangle[] = {
        { DirectX::XMFLOAT3(0.0f,  0.5f, 0.0f) },
        { DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f) },
        { DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f) }
    };

    LoadVertex(triangle, sizeof(Vertex), ARRAYSIZE(triangle),
        m_vs_blob->GetBufferPointer(), (UINT)(m_vs_blob->GetBufferSize()));

    // Set vertex buffer
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_context->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride, &offset);

    // Draw
    m_context->Draw(3, 0);

    // Present
    m_swap_chain->Present(1, 0);
}
