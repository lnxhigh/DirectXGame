#include "Graphics/Renderer.h"

#include "Graphics/Vertex.h"
#include "Scene/Component/MaterialComponent.h"
#include "Scene/Component/MeshComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Window/Window.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

bool Renderer::Init(Window* window)
{
    // Interface

    m_device.Init();
    m_context.Init(m_device.GetContext());
    m_swap_chain.Init(window, m_device.Get());

    // Frame buffer

    m_frame_buffer.CreateRenderTarget(m_device.Get(), m_swap_chain.GetSwapChain());
    m_frame_buffer.CreateDepthStencil(window, m_device.Get(), m_swap_chain.GetSwapChain());

    // Buffer

    m_matrix_buffer.Create(m_device.Get());

    // Viewport

    m_viewport.Init(window);

    return true;
}

void Renderer::BeginFrame()
{
    float color[] = { 0.8f, 0.8f, 0.8f, 1.0f };

    m_context.Get()->OMSetRenderTargets(1, m_frame_buffer.GetRTVAddress(), m_frame_buffer.GetDSV());
    m_context.Get()->ClearRenderTargetView(m_frame_buffer.GetRTV(), color);
    m_context.Get()->ClearDepthStencilView(m_frame_buffer.GetDSV(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::SetupScene(Scene& scene)
{
    // Matrix buffer

    XMMATRIX view = scene.GetCamera().GetViewMatrix();
    XMMATRIX proj = scene.GetCamera().GetProjectionMatrix();

    auto& matrix_data = m_matrix_buffer.Data();
    XMStoreFloat4x4(&matrix_data.view, XMMatrixTranspose(view));
    XMStoreFloat4x4(&matrix_data.proj, XMMatrixTranspose(proj));

    // Light 

    auto& light = scene.GetLight();
    light.Bind(m_context.Get());
    light.Update(m_context.Get());

    // Camera

    auto& camera = scene.GetCamera();
    camera.Bind(m_context.Get());
    camera.Update(m_context.Get());

    // Viewport

    m_viewport.Bind(m_context.Get());
}

void Renderer::DrawScene(Scene& scene)
{
    // Draw entities

    auto& entities = scene.GetEntities();

    for (const auto& entity : entities)
    {
        // Transform

        if (auto* transform = entity->GetComponent<TransformComponent>())
        {
            XMMATRIX world = transform->GetWorldMatrix();
            auto& matrix_data = m_matrix_buffer.Data();
            XMStoreFloat4x4(&matrix_data.world, XMMatrixTranspose(world));

            XMMATRIX world_inv_transpose = XMMatrixTranspose(XMMatrixInverse(nullptr, world));
            XMStoreFloat4x4(&matrix_data.world_inv_transpose, XMMatrixTranspose(world_inv_transpose));

            m_matrix_buffer.Update(m_context.Get());
            m_matrix_buffer.Bind(m_context.Get(), ShaderStage::Vertex, 0);
        }

        // Material

        if (auto* material_component = entity->GetComponent<MaterialComponent>())
        {
            if (Material* material = material_component->GetMaterial())
            {
                material->Update(m_context.Get());
                material->Bind(m_context.Get());
            }
        }

        // Mesh

        if (auto* mesh_component = entity->GetComponent<MeshComponent>())
        {
            if (Mesh* mesh = mesh_component->GetMesh())
            {
                mesh->Bind(m_context.Get());
                m_context.Get()->DrawIndexed(mesh->GetIndexBuffer().GetIndexCount(), 0, 0);
            }
        }
    }
}

void Renderer::EndFrame()
{
    // Present

    m_swap_chain.Present();
}

void Renderer::Render(Scene& scene)
{
    BeginFrame();
    SetupScene(scene);
    DrawScene(scene);
    EndFrame();
}
