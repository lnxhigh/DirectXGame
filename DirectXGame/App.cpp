#include "App.h"

#include <DirectXMath.h>
#include "Vertex.h"

using namespace DirectX;

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

App::App(HINSTANCE h_instance, int cmd_show)
{
    m_window.Init(h_instance, cmd_show, &m_input_system);
    m_renderer.Init(&m_window);
    m_timer = Timer();
    m_camera.Init(&m_input_system);
}

App::~App()
{

}

bool App::Init()
{
    m_timer.Reset();
    m_camera.SetPerspective(0.75f, m_window.GetAspectRatio(), 0.1f, 100.0f);

    LoadResources();
    LoadScene();

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
        m_renderer.Render(m_entities, m_camera);
    }

    return 0;
}

void App::LoadResources()
{
    // Load mesh

    m_mesh.GetVertexBuffer().Create(m_renderer.GetDevice().Get(), vertices, sizeof(Vertex), ARRAYSIZE(vertices));
    m_mesh.GetIndexBuffer().Create(m_renderer.GetDevice().Get(), indices, ARRAYSIZE(indices));

    // Load material

    m_material.GetVertexShader().Compile(L"VertexShader.hlsl");
    m_material.GetVertexShader().Create(m_renderer.GetDevice().Get());

    m_material.GetPixelShader().Compile(L"PixelShader.hlsl");
    m_material.GetPixelShader().Create(m_renderer.GetDevice().Get());

    m_material.GetInputLayout().Create(
        m_renderer.GetDevice().Get(),
        m_material.GetVertexShader().GetShaderBlob()->GetBufferPointer(),
        m_material.GetVertexShader().GetShaderBlob()->GetBufferSize()
    );
}

void App::LoadScene()
{
    // First entity

    std::unique_ptr<Entity> entity = std::make_unique<Entity>();
    entity->AddComponent<TransformComponent>();
    entity->AddComponent<MeshComponent>(&m_mesh);
    entity->AddComponent<MaterialComponent>(&m_material);
    m_entities.push_back(std::move(entity));

    // Second entity

    std::unique_ptr<Entity> other = std::make_unique<Entity>();
    auto* transform = other->AddComponent<TransformComponent>();
    other->AddComponent<MeshComponent>(&m_mesh);
    other->AddComponent<MaterialComponent>(&m_material);

    transform->position = XMFLOAT3(2.0f, 2.0f, 2.0f);
    transform->rotation = XMFLOAT3(1.0f, 2.0f, 3.0f);
    transform->scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

    m_entities.push_back(std::move(other));
}
