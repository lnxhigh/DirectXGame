#include "Core/App.h"

#include <memory>
#include <vector>
#include <DirectXMath.h>

#include "External/tiny_obj_loader.h"
#include "Graphics/Vertex.h"

#include "Resource/Loader/MeshLoader.h"

using namespace DirectX;

App::App(HINSTANCE h_instance, int cmd_show)
{
    m_window.Init(h_instance, cmd_show, &m_input_system);
    m_renderer.Init(&m_window);
    m_timer = Timer();
    m_scene.Init(&m_window, m_renderer.GetDevice().Get(), &m_input_system);
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
        m_scene.Update(m_timer.DeltaTime());
        m_renderer.Render(m_scene);
    }

    return 0;
}

void App::LoadResources(ID3D11Device* device, ID3D11DeviceContext* context)
{
    // Register loaders

    m_resource_manager.RegisterLoader<Mesh, MeshDescriptor>(std::make_unique<MeshLoader>());

    // Import model
    
    MeshDescriptor desc;
    desc.id = "cottage";
    desc.name = "cottage";
    desc.type = "mesh";
    desc.path = "../DirectXGame/Assets/Models/cottage/cottage_obj.obj";

    std::shared_ptr<void> raw = m_resource_manager.Load(desc, m_renderer.GetDevice().Get());
    std::shared_ptr<Mesh> cottage = std::static_pointer_cast<Mesh>(raw);
    
    m_mesh = *cottage.get();

    // Load primitive mesh
    // 
    // m_icosahedron = Icosahedron(1.0f);
    // std::vector<Vertex>& vertices = m_icosahedron.vertices;
    // std::vector<unsigned int>& indices = m_icosahedron.indices;
    // 
    // Load material

    const wchar_t* vs_path = L"../DirectXGame/Assets/Shaders/Vertex/VertexShader.hlsl";
    const wchar_t* ps_path = L"../DirectXGame/Assets/Shaders/Pixel/PixelShader.hlsl";

    m_material.Init(device, vs_path, ps_path);

    m_material.SetDiffuse(XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f));
    m_material.SetSpecular(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
    m_material.SetShininess(8.0f);
}

void App::LoadScene(ID3D11DeviceContext* context)
{
    // First entity

    std::shared_ptr<Entity> entity = std::make_unique<Entity>();

    //// Add component

    entity->AddComponent<TransformComponent>();
    entity->AddComponent<MeshComponent>(&m_mesh);
    entity->AddComponent<MaterialComponent>(&m_material);

    m_scene.AddEntity(entity);

    /*
    
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

    m_scene.AddEntity(other);

    */
}
