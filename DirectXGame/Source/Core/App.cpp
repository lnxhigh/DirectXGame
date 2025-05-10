#include "Core/App.h"

#include <memory>
#include <vector>
#include <DirectXMath.h>

#include "External/tiny_obj_loader.h"
#include "Graphics/Vertex.h"

#include "Resource/Loader/MeshLoader.h"
#include "Resource/Loader/TextureLoader.h"
#include "Resource/Loader/ShaderLoader.h"

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
    //
    // m_resource_manager.RegisterLoader<Mesh, MeshDescriptor>(std::make_unique<MeshLoader>());
    // std::shared_ptr<Mesh> cottage = m_resource_manager.Load<Mesh, MeshDescriptor>(desc, m_renderer.GetDevice().Get());

    // Load primitive mesh
    // 
    // m_icosahedron = Icosahedron(1.0f);
    // std::vector<Vertex>& vertices = m_icosahedron.vertices;
    // std::vector<unsigned int>& indices = m_icosahedron.indices;

    // Load model
    
    MeshDescriptor mesh_desc = {};
    mesh_desc.id = "cottage";
    mesh_desc.name = "cottage";
    mesh_desc.type = "mesh";
    mesh_desc.path = "../DirectXGame/Assets/Models/cottage/cottage_obj.obj";

    auto mesh_loader = MeshLoader();
    std::shared_ptr<Mesh> cottage = mesh_loader.Load(mesh_desc, m_renderer.GetDevice().Get());
    m_mesh = *cottage.get();

    // Load Texture

    TextureDescriptor tex_desc = {};
    tex_desc.id = "cottage_texture";
    tex_desc.name = "cottage_texture";
    tex_desc.type = "texture";
    tex_desc.path = "../DirectXGame/Assets/Textures/cottage_textures/cottage_diffuse.png";

    auto texture_loader = TextureLoader();
    auto diffuse_map = texture_loader.Load(tex_desc, m_renderer.GetDevice().Get());
    m_material.diffuse_map = diffuse_map;

    // Load Shader

    ShaderDescriptor shader_desc = {};
    shader_desc.id = "default_shader";
    shader_desc.name = "default_shader";
    shader_desc.type = "shader";
    shader_desc.vertex_shader_path = "../DirectXGame/Assets/Shaders/Vertex/VertexShader.hlsl";
    shader_desc.pixel_shader_path = "../DirectXGame/Assets/Shaders/Pixel/PixelShader.hlsl";

    auto shader_loader = ShaderLoader();
    auto shader = shader_loader.Load(shader_desc, m_renderer.GetDevice().Get());
    m_material.shader = shader;

    // Load material

    m_material.Init(device);
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
