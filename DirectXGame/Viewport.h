#pragma once
#include <d3d11.h>

class Window;

class Viewport
{
private:
    D3D11_VIEWPORT m_viewport = {};

public:
    Viewport() = default;
    void Init(const Window* window);
    void Resize(int width, int height);

    const D3D11_VIEWPORT& Get() const { return m_viewport; }
};
