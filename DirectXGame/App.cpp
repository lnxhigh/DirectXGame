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
    m_camera.Init(&m_input_system);
}

App::~App()
{

}

bool App::Init()
{
    m_timer.Reset();

    LoadResources(m_renderer.GetDevice().Get());
    LoadScene(m_renderer.GetDevice().Get(), m_renderer.GetContext().Get());

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

void App::LoadResources(ID3D11Device* device)
{
    // Load mesh

    //// Import model

    m_cube = Cube(2.0f);
    m_sphere = Icosahedron(1.0f);

    // std::vector<Vertex>& vertices = m_cube.vertices;
    // std::vector<unsigned int>& indices = m_cube.indices;
    // GeometryUtil::ComputeNormals(vertices.data(), (UINT)vertices.size(), indices.data(), (UINT)indices.size());

    std::vector<Vertex>& vertices = m_sphere.vertices;
    std::vector<unsigned int>& indices = m_sphere.indices; 
    GeometryUtil::ComputeNormals(vertices.data(), (UINT)vertices.size(), indices.data(), (UINT)indices.size());

    //// Create buffer

    m_mesh.GetVertexBuffer().Create(device, vertices.data(), sizeof(Vertex), (UINT) vertices.size());
    m_mesh.GetIndexBuffer().Create(device, indices.data(), (UINT) indices.size());

    // Load material

    m_material.GetVertexShader().Compile(L"VertexShader.hlsl");
    m_material.GetVertexShader().Create(device);

    m_material.GetPixelShader().Compile(L"PixelShader.hlsl");
    m_material.GetPixelShader().Create(device);

    m_material.GetInputLayout().Create(
        device,
        m_material.GetVertexShader().GetShaderBlob()->GetBufferPointer(),
        m_material.GetVertexShader().GetShaderBlob()->GetBufferSize()
    );
}

void App::LoadScene(ID3D11Device* device, ID3D11DeviceContext* context)
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

    // Light
    
    //// Set logical data

    m_light.SetColor(XMFLOAT4(1, 1, 1, 1));
    m_light.SetDirection(XMFLOAT3(0, -1, +1));
    m_light.SetAmbient(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));

    //// Create + Update + Bind

    m_light_buffer.Create(device);

    auto& light_data = m_light_buffer.Data();
    light_data.color = m_light.GetColor();
    light_data.direction = m_light.GetDirection();
    light_data.ambient = m_light.GetAmbient();
    m_light_buffer.Update(context);

    m_light_buffer.Bind(context, ShaderStage::Pixel, 1); // b1 in pixel shader

    // Material

    m_material_buffer.Create(device);

    auto& material_data = m_material_buffer.Data();
    material_data.diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
    material_data.specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
    material_data.shininess = 8.0f;
    m_material_buffer.Update(context);

    m_material_buffer.Bind(context, ShaderStage::Pixel, 2); // b2 in pixel shader

    // Camera

    //// Set logical data

    XMFLOAT4 eye = XMFLOAT4(6.0f, 0.0f, -6.0f, 1.0f);
    XMFLOAT4 at = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
    XMFLOAT4 up = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);
    
    m_camera.SetTransform(eye, at, up);
    m_camera.SetPerspective(0.75f, m_window.GetAspectRatio(), 0.1f, 100.0f);

    //// Create + Update + Bind

    m_camera_buffer.Create(device);
    
    auto& camera_data = m_camera_buffer.Data();
    XMStoreFloat3(&camera_data.position, m_camera.GetPosition());
    m_camera_buffer.Update(context);

    m_camera_buffer.Bind(context, ShaderStage::Pixel, 3); // b3 in pixel shader
}
