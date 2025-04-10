#include "Window.h"
#include "InputSystem.h"
#include <windowsx.h>

bool Window::Init(HINSTANCE h_instance, int cmd_show, InputSystem* input_system)
{   
    // Set the input system before creating a window

    m_input_system = input_system;

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
    {
        PostQuitMessage(0);

        return 0;
    }

    case WM_CREATE:
    {
        m_input_system->Init(hwnd);

        return 0;
    }

    case WM_INPUT:
    {
        UINT dw_size = 0;
        if (GetRawInputData((HRAWINPUT)l_param, RID_INPUT, nullptr, &dw_size, sizeof(RAWINPUTHEADER)) != 0)
            return 0;

        if (m_input_buffer.size() < dw_size)
            m_input_buffer.resize(dw_size);

        if (GetRawInputData((HRAWINPUT)l_param, RID_INPUT, m_input_buffer.data(), &dw_size, sizeof(RAWINPUTHEADER)) != dw_size)
            return 0;

        RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(m_input_buffer.data());
        m_input_system->Update(raw);

        return 0;
    }

    case WM_SIZE:
    {
        int width = LOWORD(l_param);
        int height = HIWORD(l_param);

        // Update window size

        m_width = width;
        m_height = height;

        // Notify event

        // ... OnResize(width, height);

        return 0;
    }
        
    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);
}
