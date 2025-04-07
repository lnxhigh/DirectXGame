#include "Renderer.h"
#include "Vertex.h"

using Microsoft::WRL::ComPtr;

bool Renderer::Init(Window* window)
{
    // Rendering pipeline

    device.Init();
    context.Init(device.GetContext());
    swap_chain.Init(window, device.Get());

    frame_buffer.CreateRenderTarget(device.Get(), swap_chain.GetSwapChain());
    frame_buffer.CreateDepthStencil(window, device.Get(), swap_chain.GetSwapChain());

    shader_manager.Init(device.Get());
    shader_manager.LoadVertexShader(L"VertexShader.hlsl");
    shader_manager.LoadPixelShader(L"PixelShader.hlsl");

    viewport_manager.Init(window);

    // Data Loader

    vertex_buffer.Init(device.Get());

    return true;
}

void Renderer::BeginFrame()
{
    context.Get()->OMSetRenderTargets(1, frame_buffer.GetRTVAddress(), frame_buffer.GetDSV());

    float color[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    context.Get()->ClearRenderTargetView(frame_buffer.GetRTV(), color);
    context.Get()->ClearDepthStencilView(frame_buffer.GetDSV(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::SetupPipeline()
{
    context.Get()->IASetInputLayout(vertex_buffer.GetInputLayout());
    context.Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context.Get()->VSSetShader(shader_manager.GetVertexShader(), nullptr, 0);
    context.Get()->RSSetViewports(1, &viewport_manager.GetViewport());
    context.Get()->PSSetShader(shader_manager.GetPixelShader(), nullptr, 0);
}

void Renderer::DrawScene()
{
    Vertex triangle[] = {
        { DirectX::XMFLOAT3(0.0f,  0.5f, 0.0f) },
        { DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f) },
        { DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f) }
    };

    vertex_buffer.Load(triangle, sizeof(Vertex), ARRAYSIZE(triangle),
        shader_manager.GetVertexShaderBlob()->GetBufferPointer(),
        shader_manager.GetVertexShaderBlob()->GetBufferSize()
    );

    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    context.Get()->IASetVertexBuffers(0, 1, vertex_buffer.GetVertexBufferAddress(), &stride, &offset);
    context.Get()->Draw(3, 0);
}

void Renderer::EndFrame()
{
    swap_chain.Present();
}

void Renderer::Render()
{
    BeginFrame();
    SetupPipeline();
    DrawScene();
    EndFrame();
}
