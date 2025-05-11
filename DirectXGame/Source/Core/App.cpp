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

    auto mesh_loader = MeshLoader();

    //// cottage
    
    MeshDescriptor cottage_mesh_desc = {};
    cottage_mesh_desc.id = "cottage";
    cottage_mesh_desc.name = "cottage";
    cottage_mesh_desc.type = "mesh";
    cottage_mesh_desc.path = "../DirectXGame/Assets/Models/cottage/cottage_obj.obj";

    std::shared_ptr<Mesh> cottage = mesh_loader.Load(cottage_mesh_desc, m_renderer.GetDevice().Get());
    m_cottage_mesh = cottage;

    //// watchtower

    MeshDescriptor watchtower_mesh_desc = {};
    watchtower_mesh_desc.id = "watchtower";
    watchtower_mesh_desc.name = "watchtower";
    watchtower_mesh_desc.type = "mesh";
    watchtower_mesh_desc.path = "../DirectXGame/Assets/Models/watchtower/wooden watch tower2.obj";

    std::shared_ptr<Mesh> watchtower = mesh_loader.Load(watchtower_mesh_desc, m_renderer.GetDevice().Get());
    m_watchtower_mesh = watchtower;

    // Load Texture

    auto texture_loader = TextureLoader();

    //// cottage

    TextureDescriptor cottage_tex_desc = {};
    cottage_tex_desc.id = "cottage_texture";
    cottage_tex_desc.name = "cottage_texture";
    cottage_tex_desc.type = "texture";
    cottage_tex_desc.path = "../DirectXGame/Assets/Textures/cottage_textures/cottage_diffuse.png";

    auto cottage_diffuse_map = texture_loader.Load(cottage_tex_desc, m_renderer.GetDevice().Get());
    m_cottage_material->diffuse_map = cottage_diffuse_map;

    //// watchtower

    TextureDescriptor watchtower_tex_desc = {};
    watchtower_tex_desc.id = "watchtower_texture";
    watchtower_tex_desc.name = "watchtower_texture";
    watchtower_tex_desc.type = "texture";
    watchtower_tex_desc.path = "../DirectXGame/Assets/Textures/watchtower_textures/Wood_Tower_Col.png";

    auto watchtower_diffuse_map = texture_loader.Load(watchtower_tex_desc, m_renderer.GetDevice().Get());
    m_watchtower_material->diffuse_map = watchtower_diffuse_map;

    // Load Shader

    auto shader_loader = ShaderLoader();

    ShaderDescriptor shader_desc = {};
    shader_desc.id = "default_shader";
    shader_desc.name = "default_shader";
    shader_desc.type = "shader";
    shader_desc.vertex_shader_path = "../DirectXGame/Assets/Shaders/Vertex/VertexShader.hlsl";
    shader_desc.pixel_shader_path = "../DirectXGame/Assets/Shaders/Pixel/PixelShader.hlsl";

    auto shader = shader_loader.Load(shader_desc, m_renderer.GetDevice().Get());

    //// cottage

    m_cottage_material->shader = shader;

    //// watchtower

    m_watchtower_material->shader = shader;

    // Load material

    //// cottage

    m_cottage_material->Init(device);

    auto& cottage_material_data = m_cottage_material->material_data;

    cottage_material_data.diffuse = XMFLOAT4(0.64f, 0.64f, 0.64f, 1.0f);
    cottage_material_data.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
    cottage_material_data.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    cottage_material_data.emissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
    
    cottage_material_data.shininess = 2.0f;

    //// watchtower

    m_watchtower_material->Init(device);

    auto& watchtower_material_data = m_cottage_material->material_data;

    watchtower_material_data.diffuse = XMFLOAT4(0.397386f, 0.397386f, 0.397386f, 1.0f);
    watchtower_material_data.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
    watchtower_material_data.ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    watchtower_material_data.emissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

    watchtower_material_data.shininess = 1.0f;
}

void App::LoadScene(ID3D11DeviceContext* context)
{
    // First entity

    std::shared_ptr<Entity> entity = std::make_unique<Entity>();

    //// Add component

    entity->AddComponent<TransformComponent>();
    entity->AddComponent<MeshComponent>(m_cottage_mesh);
    entity->AddComponent<MaterialComponent>(m_cottage_material);

    m_scene.AddEntity(entity);
    
    // Second entity

    std::shared_ptr<Entity> other = std::make_unique<Entity>();

    //// Add component

    auto* transform = other->AddComponent<TransformComponent>();
    other->AddComponent<MeshComponent>(m_watchtower_mesh);
    other->AddComponent<MaterialComponent>(m_watchtower_material);

    //// Set component

    transform->position = XMFLOAT3(-30.0f, -3.0f, -20.0f);
    transform->rotation = XMFLOAT3(0.0f, 1.57f, 0.0f);
    transform->scale = XMFLOAT3(5.0f, 5.0f, 5.0f);

    m_scene.AddEntity(other);
}
