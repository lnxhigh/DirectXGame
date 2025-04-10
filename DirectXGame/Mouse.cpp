#include "Mouse.h"
#include <vector>

bool Mouse::Init(HWND hwnd)
{
    RAWINPUTDEVICE device = { };
    device.usUsagePage = 0x01; // Generic Desktop Controls
    device.usUsage = 0x02; // Mouse
    device.dwFlags = 0; // Receive input when focused
    device.hwndTarget = hwnd;

    if (!RegisterRawInputDevices(&device, 1, sizeof(device)))
    {
        OutputDebugStringA("Error: Failed to register mouse\n");
        return false;
    }

    return true;
}

bool Mouse::Update(RAWINPUT* input)
{
    m_dx = input->data.mouse.lLastX;
    m_dy = input->data.mouse.lLastY;

    return true;
}
