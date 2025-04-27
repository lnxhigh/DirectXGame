#pragma once

#include <memory>
#include <vector>

#include "Core/Timer.h"

#include "Graphics/Buffer/CameraBuffer.h"
#include "Graphics/Buffer/LightBuffer.h"
#include "Graphics/Buffer/MaterialBuffer.h"
#include "Graphics/Renderer.h"

#include "Input/InputSystem.h"

#include "Scene/Camera.h"
#include "Scene/Component/MeshComponent.h"
#include "Scene/Component/MaterialComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Entity/Entity.h"
#include "Scene/Light.h"

#include "Resource/Material.h"
#include "Resource/Mesh.h"

#include "Resource/Primitive/Cube.h"
#include "Resource/Primitive/Icosahedron.h"

#include "Window/Window.h"

class App
{
public:
    App(HINSTANCE h_instance, int cmd_show);
    ~App();

    bool Init();
    
    void LoadResources(ID3D11Device* device, ID3D11DeviceContext* context);
    void LoadScene(ID3D11DeviceContext* context);

    int Run();

private:
    Window m_window;
    Renderer m_renderer;
    InputSystem m_input_system;
    Timer m_timer;
    
    Light m_light;
    Camera m_camera;

    Mesh m_mesh;
    Cube m_cube;
    Icosahedron m_icosahedron;

    Material m_material;
    std::vector<std::unique_ptr<Entity>> m_entities;
};
