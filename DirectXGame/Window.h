#include <windows.h>

class Window
{
private:
    HINSTANCE m_h_instance;
    HINSTANCE m_h_prev_instance;
    PWSTR m_p_cmd_line;
    int m_cmd_show;
    HWND m_hwnd = nullptr;
    const wchar_t* m_class_name = L"Window Class";
    const wchar_t* m_window_title = L"DirectX Application";

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param);

public:
    Window(HINSTANCE h_instance, HINSTANCE h_prev_instance, PWSTR p_cmd_line, int cmd_show);
    ~Window();

    void RegisterWindowClass(HINSTANCE h_instance);
    void CreateAppWindow(HINSTANCE h_instance);
    HWND GetHandle() const { return m_hwnd; }
};
