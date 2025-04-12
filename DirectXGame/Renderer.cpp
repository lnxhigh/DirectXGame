#include "Renderer.h"
#include "Window.h"
#include "Vertex.h"

#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"

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

    // Matrix buffer

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

void Renderer::SetupPipeline(const Camera& camera)
{
    // Matrix buffer

    XMMATRIX view = camera.GetViewMatrix();
    XMMATRIX proj = camera.GetProjectionMatrix();

    m_matrix_buffer.SetViewMatrix(view);
    m_matrix_buffer.SetProjectionMatrix(proj);

    // Viewport

    m_context.Bind(m_viewport);
}

void Renderer::DrawScene(const std::vector<std::unique_ptr<Entity>>& entities)
{
    // Draw entities

    for (const auto& entity : entities)
    {
        // Transform

        if (auto* transform = entity->GetComponent<TransformComponent>())
        {
            XMMATRIX world = transform->GetWorldMatrix();
            m_matrix_buffer.SetWorldMatrix(world);
            m_context.Bind(m_matrix_buffer);
        }

        // Material

        if (auto* material_component = entity->GetComponent<MaterialComponent>())
        {
            if (Material* material = material_component->GetMaterial())
            {
                m_context.Bind(*material);
            }
        }

        // Mesh

        if (auto* mesh_component = entity->GetComponent<MeshComponent>())
        {
            if (Mesh* mesh = mesh_component->GetMesh())
            {
                m_context.Bind(*mesh);
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

void Renderer::Render(std::vector<std::unique_ptr<Entity>>& entities, const Camera& camera)
{
    BeginFrame();
    SetupPipeline(camera);
    DrawScene(entities);
    EndFrame();
}
