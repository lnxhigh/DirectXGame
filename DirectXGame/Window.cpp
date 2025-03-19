#include <iostream>
#include "Window.h"

Window::Window(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
    : m_hInstance(hInstance), m_hPrevInstance(hPrevInstance),
    m_pCmdLine(pCmdLine), m_nCmdShow(nCmdShow)
{
    RegisterWindowClass(hInstance);
    CreateAppWindow(hInstance);
}

Window::~Window()
{

}

void Window::RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = m_className;

    if (!RegisterClass(&wc))
    {
        std::cerr << "Error: Failed to register window class!" << std::endl;
        exit(-1);
    }
}

void Window::CreateAppWindow(HINSTANCE hInstance)
{
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        m_className,                   // Window class
        m_windowTitle,                 // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,         // Parent window    
        NULL,         // Menu
        hInstance,    // Instance handle
        NULL          // Additional application data
    );

    if (!hwnd) {
        std::cerr << "Failed to create window" << std::endl;
        exit(-1);
    }
    
    m_hwnd = hwnd;
    ShowWindow(m_hwnd, m_nCmdShow);
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
