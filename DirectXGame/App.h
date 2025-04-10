#pragma once

#include "Window.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "Timer.h"
#include "Camera.h"

class App
{
public:
    App(HINSTANCE h_instance, int cmd_show);
    ~App();

    bool Init();
    int Run();

private:
    Window m_window;
    Renderer m_renderer;
    InputSystem m_input_system;
    Timer m_timer;
    Camera m_camera;
};
