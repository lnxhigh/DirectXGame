#include "App.h"

#include <vector>
#include <DirectXMath.h>

#include "Vertex.h"
#include "GeometryUtil.h"

using namespace DirectX;

App::App(HINSTANCE h_instance, int cmd_show)
{
    m_window.Init(h_instance, cmd_show, &m_input_system);
    m_renderer.Init(&m_window);
    m_timer = Timer();

    m_light.Init(m_renderer.GetDevice().Get());
    m_camera.Init(m_renderer.GetDevice().Get(), &m_input_system);
}

App::~App()
{

}

bool App::Init()
{
    m_timer.Reset();

    LoadResources(m_renderer.GetDevice().Get(), m_renderer.GetContext().Get());
    LoadScene(m_renderer.GetContext().Get());

    return true;
}

int App::Run()
{
    MSG msg = {};
    bool is_running = true;

    while (is_running)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                is_running = false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        m_timer.Tick();
        m_camera.Update(m_timer.DeltaTime());
        m_camera.Update(m_renderer.GetContext().Get());
        m_renderer.Render(m_entities, m_light, m_camera);
    }

    return 0;
}

void App::LoadResources(ID3D11Device* device, ID3D11DeviceContext* context)
{
    // Import model

    m_icosahedron = Icosahedron(1.0f);
    std::vector<Vertex>& vertices = m_icosahedron.vertices;
    std::vector<unsigned int>& indices = m_icosahedron.indices;

    // Load mesh

    m_mesh.Init(
        device,
        vertices.data(), sizeof(Vertex), (UINT)vertices.size(),
        indices.data(), (UINT)indices.size()
    );

    // Load material

    m_material.Init(device, L"VertexShader.hlsl", L"PixelShader.hlsl");

    m_material.SetDiffuse(XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
    m_material.SetSpecular(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
    m_material.SetShininess(8.0f);

    m_material.Update(context);
}

void App::LoadScene(ID3D11DeviceContext* context)
{
    // Light

    m_light.SetColor(XMFLOAT4(1, 1, 1, 1));
    m_light.SetDirection(XMFLOAT3(0, -1, +1));
    m_light.SetAmbient(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));

    m_light.Update(context);

    // Camera

    XMFLOAT4 eye = XMFLOAT4(6.0f, 0.0f, -6.0f, 1.0f);
    XMFLOAT4 at = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
    XMFLOAT4 up = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);

    m_camera.SetTransform(eye, at, up);
    m_camera.SetPerspective(0.75f, m_window.GetAspectRatio(), 0.1f, 100.0f);

    m_camera.Update(context);

    // First entity

    std::unique_ptr<Entity> entity = std::make_unique<Entity>();

    //// Add component

    entity->AddComponent<TransformComponent>();
    entity->AddComponent<MeshComponent>(&m_mesh);
    entity->AddComponent<MaterialComponent>(&m_material);

    m_entities.push_back(std::move(entity));

    // Second entity

    std::unique_ptr<Entity> other = std::make_unique<Entity>();

    //// Add component

    auto* transform = other->AddComponent<TransformComponent>();
    other->AddComponent<MeshComponent>(&m_mesh);
    other->AddComponent<MaterialComponent>(&m_material);

    //// Set component

    transform->position = XMFLOAT3(2.0f, 2.0f, 2.0f);
    transform->rotation = XMFLOAT3(1.0f, 2.0f, 3.0f);
    transform->scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

    m_entities.push_back(std::move(other));
}
