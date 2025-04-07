#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Timer.h"

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
    Timer m_timer;
};
