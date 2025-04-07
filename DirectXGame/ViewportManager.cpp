#include "ViewportManager.h"
#include "Window.h"

bool ViewportManager::Init(Window* window)
{
    D3D11_VIEWPORT viewport = { };

    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    viewport.Width = (float)window->GetWidth();
    viewport.Height = (float)window->GetHeight();
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    m_viewport = viewport;

    return true;
}
