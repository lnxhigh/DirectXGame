#pragma once

#include <memory>
#include <vector>

#include "Window.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "Timer.h"

#include "Camera.h"
#include "Light.h"

#include "Entity.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"

#include "LightBuffer.h"
#include "MaterialBuffer.h"
#include "CameraBuffer.h"

#include "Cube.h"
#include "Icosahedron.h"

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
