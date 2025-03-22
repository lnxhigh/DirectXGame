#include "App.h"
#include "Window.h"
#include "Renderer.h"
#include "Timer.h"

App::App(void* h_instance, int cmd_show)
	: m_window(nullptr), m_renderer(nullptr), m_timer(nullptr)
{
    m_window = std::make_unique<Window>((HINSTANCE)h_instance, cmd_show);
    m_renderer = std::make_unique<Renderer>(m_window->GetHwnd());
    m_timer = std::make_unique<Timer>();
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
            m_timer->Tick();
            m_renderer->Render();
        }
    }

    return (int)msg.wParam;
}
