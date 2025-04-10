#pragma once

#include "Device.h"
#include "Context.h"
#include "SwapChain.h"
#include "FrameBuffer.h"
#include "ShaderManager.h"
#include "ViewportManager.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "MatrixBuffer.h"

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

class Window;

using Microsoft::WRL::ComPtr;

class Renderer
{
private:
    Device m_device;
    Context m_context;
    SwapChain m_swap_chain;
    FrameBuffer m_frame_buffer;
    ShaderManager m_shader_manager;
    ViewportManager m_viewport_manager;

    VertexBuffer m_vertex_buffer;
    IndexBuffer m_index_buffer;
    MatrixBuffer m_matrix_buffer;

public:
    bool Init(Window* window);
    void Render(XMMATRIX new_view);

private:
    void BeginFrame(); // Clear and set render target
    void SetupPipeline(); // Viewport, Shader, InputLayout
    void DrawScene(); // Draw 
    void EndFrame(); // Present

};
