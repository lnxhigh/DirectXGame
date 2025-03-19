#include <windows.h>

class Window
{
private:
    HINSTANCE m_hInstance;
    HINSTANCE m_hPrevInstance;
    PWSTR m_pCmdLine;
    int m_nCmdShow;
    HWND m_hwnd = nullptr;
    const wchar_t* m_className = L"Window Class";
    const wchar_t* m_windowTitle = L"DirectX Application";

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    Window(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
    ~Window();

    void RegisterWindowClass(HINSTANCE hInstance);
    void CreateAppWindow(HINSTANCE hInstance);
    HWND GetHandle() const { return m_hwnd; }
};
