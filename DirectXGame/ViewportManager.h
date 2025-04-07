#pragma once

#include <d3d11.h>

class Window;

class ViewportManager
{
private:
	D3D11_VIEWPORT m_viewport;

public:
	bool Init(Window* window);
	const D3D11_VIEWPORT& GetViewport() const { return m_viewport; }
};
