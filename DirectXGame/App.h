#pragma once

#include <memory>
#include <vector>

#include "Window.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "Timer.h"
#include "Camera.h"

#include "Entity.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"

class App
{
public:
    App(HINSTANCE h_instance, int cmd_show);
    ~App();

    bool Init();
    
    void LoadResources();
    void LoadScene();

    int Run();

private:
    Window m_window;
    Renderer m_renderer;
    InputSystem m_input_system;
    Timer m_timer;
    Camera m_camera;

    Mesh m_mesh;
    Material m_material;
    std::vector<std::unique_ptr<Entity>> m_entities;
};
