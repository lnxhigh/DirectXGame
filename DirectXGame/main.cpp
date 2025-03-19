#include "Window.h"
#include "Renderer.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Window window = Window(hInstance, hPrevInstance, pCmdLine, nCmdShow);
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

