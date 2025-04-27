#include "Input/Keyboard.h"

bool Keyboard::Init(HWND hwnd)
{
    RAWINPUTDEVICE device = { };
    device.usUsagePage = 0x01; // Generic Desktop Controls
    device.usUsage = 0x06; // Keyboard
    device.dwFlags = 0; // Receive input when focused
    device.hwndTarget = hwnd;

    if (!RegisterRawInputDevices(&device, 1, sizeof(RAWINPUTDEVICE)))
    {
        OutputDebugStringA("Error: Failed to register keyboard\n");
        return false;
    }

    return true;
}

bool Keyboard::Update(RAWINPUT* input)
{
    const RAWKEYBOARD& keyboard = input->data.keyboard;
    int key_code = keyboard.VKey;
    bool key_down = !(keyboard.Flags & RI_KEY_BREAK); // RI_KEY_BREAK: key up

    m_key_code = key_code;
    m_key_down = key_down;

    if (key_code < 256)
    {
        m_key_state[key_code] = key_down;
    }

    return true;
}

bool Keyboard::IsKeyActive(int key) const
{
    if (key >= 0 && key < 256)
    {
        return m_key_state[key];
    }
    
    return false;
}
