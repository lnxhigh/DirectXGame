#include "InputSystem.h"
#include "InputListener.h"
#include "windows.h"

bool InputSystem::Init(HWND hwnd)
{
	m_mouse.Init(hwnd);
	m_keyboard.Init(hwnd);
	
	return true;
}

bool InputSystem::Update(RAWINPUT* input)
{
	switch (input->header.dwType)
	{

	case RIM_TYPEKEYBOARD:
	{
		// Update

		m_keyboard.Update(input);

		// Notify

		if (m_keyboard.IsKeyDown())
		{
			for (InputListener* listener : m_listeners)
			{
				listener->OnKeyDown(m_keyboard.GetKey());
			}
		}

		break;
	}

	case RIM_TYPEMOUSE:
	{
		// Update

		m_mouse.Update(input);
		
		// Notify

		if (m_mouse.GetDeltaX() != 0 || m_mouse.GetDeltaY() != 0)
		{
			for (InputListener* listener : m_listeners)
			{
				listener->OnMouseMove(m_mouse.GetDeltaX(), m_mouse.GetDeltaY());
			}

			m_mouse.ResetDelta();
		}

		break;
	}
		
	}

	return true;
}

void InputSystem::RegisterListener(InputListener* listener)
{
	m_listeners.push_back(listener);
}
