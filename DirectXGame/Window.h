#pragma once

#include <windows.h>

class Window
{
private:
    HINSTANCE m_h_instance;
    int m_cmd_show;

    HWND m_hwnd = nullptr;
    const wchar_t* m_class_name = L"Window Class";
    const wchar_t* m_window_title = L"DirectX Application";

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);

public:
    Window(HINSTANCE h_instance, int cmd_show);
    ~Window();

    void RegisterWindowClass(HINSTANCE h_instance);
    void CreateAppWindow(HINSTANCE h_instance);
    HWND GetHwnd() const { return m_hwnd; }
};
