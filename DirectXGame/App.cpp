#include "App.h"

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
    return true;
}

int App::Run()
{
    MSG msg = { };
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
        m_renderer.Render(m_camera.GetViewMatrix());
    }

    return (int)msg.wParam;
}
