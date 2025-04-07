#pragma once

#include <windows.h>

class Window
{
private:
    HINSTANCE m_h_instance;
    int m_cmd_show;

    HWND m_hwnd = nullptr;
    int m_width;
    int m_height;

    const wchar_t* m_class_name = L"Window Class";
    const wchar_t* m_window_title = L"DirectX Application";

    static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);
    LRESULT WindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);

public:
    bool Init(HINSTANCE h_instance, int cmd_show);

    HWND GetHwnd() const { return m_hwnd; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
};
