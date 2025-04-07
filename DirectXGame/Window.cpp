#include "Window.h"

bool Window::Init(HINSTANCE h_instance, int cmd_show)
{    
    // Register window class

    WNDCLASS wc = { };
    wc.lpfnWndProc = StaticWindowProc;
    wc.hInstance = h_instance;
    wc.lpszClassName = m_class_name;

    if (!RegisterClass(&wc))
    {
        OutputDebugStringA("Error: Failed to register window class\n");
        return false;
    }
    
    // Create window

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
        this          // Additional application data
    );

    if (!hwnd) {
        OutputDebugStringA("Error: Failed to create window\n");
        return false;
    }

    // Now assign values

    m_hwnd = hwnd;
    m_h_instance = h_instance;
    m_cmd_show = cmd_show;

    RECT rect;
    GetClientRect(m_hwnd, &rect);
    m_width = rect.right - rect.left;
    m_height = rect.bottom - rect.top;

    // Show window

    ShowWindow(m_hwnd, m_cmd_show);

    return true;
}

LRESULT CALLBACK Window::StaticWindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    Window* window = nullptr;

    if (u_msg == WM_NCCREATE)
    {
        // Retrieve user data from temporary create structure
        CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(l_param);
        window = reinterpret_cast<Window*>(create->lpCreateParams);

        // Save the data permanantly
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    }
    else
    {
        window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (window)
    {
        return window->WindowProc(hwnd, u_msg, w_param, l_param);
    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);
}

LRESULT Window::WindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    switch (u_msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_SIZE:
        m_width = LOWORD(l_param);
        m_height = HIWORD(l_param);
        break;
    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);
}
