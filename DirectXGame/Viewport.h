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

public:
    void Bind(ID3D11DeviceContext* context)
    {
        context->RSSetViewports(1, &m_viewport);
    }

public:
    const D3D11_VIEWPORT& Get() const { return m_viewport; }
};
