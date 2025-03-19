#include <d3d11.h>
#include <dxgi.h>

class Renderer
{
private:
    ID3D11Device* m_device = nullptr;
    ID3D11DeviceContext* m_context = nullptr;
    IDXGISwapChain* m_swapChain = nullptr;
    ID3D11RenderTargetView* m_renderTargetView = nullptr;

public:
    Renderer(HWND hWnd);
    ~Renderer();

    void InitDevice();
    void InitSwapChain(HWND hWnd);
    void InitRenderTarget();
    void Render();
};
