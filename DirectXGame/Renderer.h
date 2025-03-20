#include <d3d11.h>
#include <dxgi.h>

class Renderer
{
private:
    ID3D11Device* m_device = nullptr;
    ID3D11DeviceContext* m_context = nullptr;
    IDXGISwapChain* m_swap_chain = nullptr;
    ID3D11RenderTargetView* m_render_target_view = nullptr;

public:
    Renderer(HWND hwnd);
    ~Renderer();

    void InitDevice();
    void InitSwapChain(HWND hwnd);
    void InitRenderTarget();
    void Render();
};
