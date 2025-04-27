#pragma once
#include <windows.h>

class IInputDevice
{
public:
	virtual bool Init(HWND hwnd) = 0;
	virtual bool Update(RAWINPUT* input) = 0;
	virtual ~IInputDevice() = default;
};
