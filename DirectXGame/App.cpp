#include "App.h"

App::App(HINSTANCE h_instance, int cmd_show)
{
    m_window.Init(h_instance, cmd_show);
    m_renderer.Init(&m_window);
    m_timer = Timer();
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

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            m_timer.Tick();
            m_renderer.Render();
        }
    }

    return (int)msg.wParam;
}
