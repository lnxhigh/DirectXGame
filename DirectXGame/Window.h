#pragma once

#include <windows.h>
#include <vector>

class InputSystem;

class Window
{
private:
    HINSTANCE m_h_instance;
    int m_cmd_show;
    HWND m_hwnd = nullptr;

    const wchar_t* m_class_name = L"Window Class";
    const wchar_t* m_window_title = L"DirectX Application";

    // Input system

    InputSystem* m_input_system;
    std::vector<BYTE> m_input_buffer;

    int m_width;
    int m_height;

    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);
    LRESULT WindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);

public:
    bool Init(HINSTANCE h_instance, int cmd_show, InputSystem* input_system);

    HWND GetHwnd() const { return m_hwnd; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
};
