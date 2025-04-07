#pragma once

#include "Device.h"
#include "Context.h"
#include "SwapChain.h"
#include "FrameBuffer.h"
#include "ShaderManager.h"
#include "ViewportManager.h"

#include "VertexBuffer.h"

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

class Window;

using Microsoft::WRL::ComPtr;

class Renderer
{
private:
    Device device;
    Context context;
    SwapChain swap_chain;
    FrameBuffer frame_buffer;
    ShaderManager shader_manager;
    ViewportManager viewport_manager;
    VertexBuffer vertex_buffer;

public:
    bool Init(Window* window);
    void Render();

private:
    void BeginFrame(); // Clear and set render target
    void SetupPipeline(); // Viewport, Shader, InputLayout
    void DrawScene(); // Draw 
    void EndFrame(); // Present

};
