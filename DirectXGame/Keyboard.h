#pragma once

#include "IInputDevice.h"
#include <windows.h>

class Keyboard : public IInputDevice
{
public:
    bool Init(HWND hwnd) override;
    bool Update(RAWINPUT* input) override;

public:
    bool IsKeyActive(int key) const;
    int GetKey() const { return m_key_code; }
    bool IsKeyDown() const { return m_key_down; }

private:    
    int m_key_code = 0;
    bool m_key_down = false;
    bool m_key_state[256] = { false };
};

