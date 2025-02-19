#include "Window.h"
#include <assert.h>
#include <iostream>

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

Window::Window()
{
    // Define and Register Window Class
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = L"WindowClass";
    wc.lpfnWndProc = WndProc;
    wc.hInstance = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    assert(::RegisterClassEx(&wc));

    // Create Window
    m_hwnd = ::CreateWindowEx(0, L"WindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

    assert(m_hwnd);

    // Display Window
    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);
}

Window::~Window()
{
    if (m_hwnd)
    {
        ::DestroyWindow(m_hwnd);
    }
}

void Window::Run()
{
    MSG msg = {};
    m_is_running = true;

    while (m_is_running)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                m_is_running = false;
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Sleep(0);
    }
}
