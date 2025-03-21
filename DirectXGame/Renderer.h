#include <d3d11.h>
#include <dxgi.h>

class Renderer
{
private:
    HWND m_hwnd = nullptr;
    UINT m_width = 0;
    UINT m_height = 0;

    ID3D11Device* m_device = nullptr;
    ID3D11DeviceContext* m_context = nullptr;
    IDXGISwapChain* m_swap_chain = nullptr;
    ID3D11RenderTargetView* m_render_target_view = nullptr;
    ID3D11DepthStencilView* m_depth_stencil_view = nullptr;

public:
    Renderer(HWND hwnd);
    ~Renderer();

    void InitWindowInfo(HWND hwnd);
    void InitDevice();
    void InitSwapChain();
    void InitRenderTarget();
    void InitDepthStencilBuffer();
    void Render();
};
