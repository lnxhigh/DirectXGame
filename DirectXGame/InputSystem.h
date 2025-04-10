#pragma once

#include "Mouse.h"
#include "Keyboard.h"

#include <windows.h>
#include <vector>

class InputListener;

class InputSystem
{
private:
	Mouse m_mouse;
	Keyboard m_keyboard;
	std::vector<InputListener*> m_listeners;

public:
	bool Init(HWND hwnd);
	bool Update(RAWINPUT* input);
	void RegisterListener(InputListener* listener);

	const Mouse& GetMouse() const { return m_mouse; }
	const Keyboard& GetKeyboard() const { return m_keyboard; }
};
