#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class Renderer
{
private:
    HWND m_hwnd = nullptr;
    UINT m_width = 0;
    UINT m_height = 0;

    // Interface
    ComPtr<ID3D11Device> m_device = nullptr;
    ComPtr<ID3D11DeviceContext> m_context = nullptr;
    ComPtr<IDXGISwapChain> m_swap_chain = nullptr;

    // View
    ComPtr<ID3D11RenderTargetView> m_render_target_view = nullptr;
    ComPtr<ID3D11DepthStencilView> m_depth_stencil_view = nullptr;
    D3D11_VIEWPORT m_viewport;

    // Shader
    ComPtr<ID3D11VertexShader> m_vertex_shader = nullptr;
    ComPtr<ID3D11PixelShader> m_pixel_shader = nullptr;
    ComPtr<ID3DBlob> m_vs_blob = nullptr;
    ComPtr<ID3DBlob> m_ps_blob = nullptr;

    // Draw
    ComPtr<ID3D11Buffer> m_vertex_buffer;
    ComPtr<ID3D11InputLayout> m_input_layout;

public:
    Renderer(HWND hwnd);
    ~Renderer();

    void InitWindowInfo(HWND hwnd);
    void InitDevice();
    void InitSwapChain();
    void InitRenderTarget();
    void InitDepthStencilBuffer();
    void InitViewport();
    
    bool InitShader(const wchar_t* vs_filename, const wchar_t* ps_filename);

    bool LoadVertex(void* vertices, unsigned int size_vertex, unsigned int size_list,
        void* shader_byte_code, unsigned int size_byte_code);

    void Render();
};
