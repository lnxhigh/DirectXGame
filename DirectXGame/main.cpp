#include "Window.h"
#include "Renderer.h"

int WINAPI wWinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, PWSTR p_cmd_line, int cmd_show)
{
    Window window = Window(h_instance, h_prev_instance, p_cmd_line, cmd_show);
    Renderer renderer = Renderer(window.GetHandle());

    MSG msg = { };

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            renderer.Render();
        }
    }

    return 0;
}

