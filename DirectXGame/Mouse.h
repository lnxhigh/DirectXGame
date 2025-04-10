#pragma once

#include "IInputDevice.h"
#include <windows.h>

class Mouse : public IInputDevice
{
public:
    bool Init(HWND hwnd) override;
    bool Update(RAWINPUT* input) override;

public:
    int GetDeltaX() const { return m_dx; }
    int GetDeltaY() const { return m_dy; }
    void ResetDelta() { m_dx = m_dy = 0; }

private:
    int m_dx = 0;
    int m_dy = 0;

};
