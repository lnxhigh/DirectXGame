#include "Renderer.h"
#include "Window.h"
#include "Vertex.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

Vertex vertices[] =
{
    { {-1.0f, -1.0f, -1.0f}, {1, 0, 0, 1} }, // 0
    { {-1.0f, +1.0f, -1.0f}, {0, 1, 0, 1} }, // 1
    { {+1.0f, +1.0f, -1.0f}, {0, 0, 1, 1} }, // 2
    { {+1.0f, -1.0f, -1.0f}, {1, 1, 0, 1} }, // 3
    { {-1.0f, -1.0f, +1.0f}, {1, 0, 1, 1} }, // 4
    { {-1.0f, +1.0f, +1.0f}, {0, 1, 1, 1} }, // 5
    { {+1.0f, +1.0f, +1.0f}, {1, 1, 1, 1} }, // 6
    { {+1.0f, -1.0f, +1.0f}, {0, 0, 0, 1} }, // 7
};

// 36 indices for the 12 triangles (2 per face)
UINT indices[] =
{
    // Front face
    0, 1, 2,
    0, 2, 3,

    // Back face
    4, 6, 5,
    4, 7, 6,

    // Left face
    4, 5, 1,
    4, 1, 0,

    // Right face
    3, 2, 6,
    3, 6, 7,

    // Top face
    1, 5, 6,
    1, 6, 2,

    // Bottom face
    4, 0, 3,
    4, 3, 7,
};

XMMATRIX world, view, proj;

bool Renderer::Init(Window* window)
{
    // Rendering pipeline

    m_device.Init();
    m_context.Init(m_device.GetContext());
    m_swap_chain.Init(window, m_device.Get());

    m_frame_buffer.CreateRenderTarget(m_device.Get(), m_swap_chain.GetSwapChain());
    m_frame_buffer.CreateDepthStencil(window, m_device.Get(), m_swap_chain.GetSwapChain());

    m_shader_manager.Init(m_device.Get());
    m_shader_manager.LoadVertexShader(L"VertexShader.hlsl");
    m_shader_manager.LoadPixelShader(L"PixelShader.hlsl");

    m_viewport_manager.Init(window);

    // Data Loader

    m_vertex_buffer.Init(m_device.Get());
    m_index_buffer.Init(m_device.Get());
    
    m_vertex_buffer.Load(vertices, sizeof(Vertex), ARRAYSIZE(vertices),
        m_shader_manager.GetVertexShaderBlob()->GetBufferPointer(),
        m_shader_manager.GetVertexShaderBlob()->GetBufferSize()
    );

    m_index_buffer.Load(indices, ARRAYSIZE(indices));

    // Set Matrix

    m_matrix_buffer.Init(m_device.Get());

    // World

    XMMATRIX rotation = XMMatrixRotationY(XMConvertToRadians(0.0f));
    XMMATRIX scale = XMMatrixScaling(0.5f, 0.5f, 0.5f);
    XMMATRIX translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
    world = scale * rotation * translation;

    // View

    XMVECTOR eye = XMVectorSet(1.0f, 1.0f, -3.0f, 1.0f);
    XMVECTOR at = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    view = XMMatrixLookAtLH(eye, at, up);

    // Projection

    constexpr float fov = XMConvertToRadians(45.0f);
    float aspect_ratio = (float)window->GetWidth() / (float)window->GetHeight();
    float near_z = 0.1f, far_z = 100.0f;
    proj = XMMatrixPerspectiveFovLH(fov, aspect_ratio, near_z, far_z);

    return true;
}

void Renderer::BeginFrame()
{
    float color[] = { 0.8f, 0.8f, 0.8f, 1.0f };

    m_context.Get()->OMSetRenderTargets(1, m_frame_buffer.GetRTVAddress(), m_frame_buffer.GetDSV());
    m_context.Get()->ClearRenderTargetView(m_frame_buffer.GetRTV(), color);
    m_context.Get()->ClearDepthStencilView(m_frame_buffer.GetDSV(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::SetupPipeline()
{
    m_context.Get()->IASetInputLayout(m_vertex_buffer.GetInputLayout());
    m_context.Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_context.Get()->VSSetShader(m_shader_manager.GetVertexShader(), nullptr, 0);
    m_context.Get()->VSSetConstantBuffers(0, 1, m_matrix_buffer.GetMatrixBufferAddress());
    m_context.Get()->RSSetViewports(1, &m_viewport_manager.GetViewport());
    m_context.Get()->PSSetShader(m_shader_manager.GetPixelShader(), nullptr, 0);
}

void Renderer::DrawScene()
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    m_context.Get()->IASetVertexBuffers(0, 1, m_vertex_buffer.GetVertexBufferAddress(), &stride, &offset);
    m_context.Get()->IASetIndexBuffer(m_index_buffer.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
    m_context.Get()->DrawIndexed(36, 0, 0);
}

void Renderer::EndFrame()
{
    m_swap_chain.Present();
}

void Renderer::Render(XMMATRIX new_view)
{
    m_matrix_buffer.SetMatrixData(m_context.Get(), world, new_view, proj);

    BeginFrame();
    SetupPipeline();
    DrawScene();
    EndFrame();
}
