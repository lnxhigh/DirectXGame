#include "Graphics/Viewport.h"

#include "Window/Window.h"

void Viewport::Init(const Window* window)
{
    Resize(window->GetWidth(), window->GetHeight());
}

void Viewport::Resize(int width, int height)
{
    m_viewport.TopLeftX = 0.0f;
    m_viewport.TopLeftY = 0.0f;
    m_viewport.Width = static_cast<float>(width);
    m_viewport.Height = static_cast<float>(height);
    m_viewport.MinDepth = 0.0f;
    m_viewport.MaxDepth = 1.0f;
}
