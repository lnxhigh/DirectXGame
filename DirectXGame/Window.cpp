#include <iostream>
#include "Window.h"

Window::Window(HINSTANCE h_instance, HINSTANCE h_prev_instance, PWSTR p_cmd_line, int cmd_show)
    : m_h_instance(h_instance), m_h_prev_instance(h_prev_instance),
    m_p_cmd_line(p_cmd_line), m_cmd_show(cmd_show)
{
    RegisterWindowClass(h_instance);
    CreateAppWindow(h_instance);
}

Window::~Window()
{

}

void Window::RegisterWindowClass(HINSTANCE h_instance)
{
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = h_instance;
    wc.lpszClassName = m_class_name;

    if (!RegisterClass(&wc))
    {
        std::cerr << "Error: Failed to register window class" << std::endl;
        exit(-1);
    }
}

void Window::CreateAppWindow(HINSTANCE h_instance)
{
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        m_class_name,                   // Window class
        m_window_title,                 // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,         // Parent window    
        NULL,         // Menu
        h_instance,   // Instance handle
        NULL          // Additional application data
    );

    if (!hwnd) {
        std::cerr << "Error: Failed to create window" << std::endl;
        exit(-1);
    }
    
    m_hwnd = hwnd;
    ShowWindow(m_hwnd, m_cmd_show);
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    switch (u_msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);
}
