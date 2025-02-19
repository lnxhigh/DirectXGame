#pragma once
#include <Windows.h>

class Window {
public:
    Window();
    ~Window();

    void Run();

private:
    HWND m_hwnd;
    bool m_is_running;
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
